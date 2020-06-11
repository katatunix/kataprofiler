#include "Mipmap.h"
#include "ImageHelper.h"
#include "log.h"

Mipmap* Mipmap::create_glTexImage2D(GLint /*internalformat*/, GLsizei width, GLsizei height, GLint border,
	GLenum format, GLenum type, const GLvoid* pixels, int unpackAlignment)
{
	if (!isValidWidthHeight(width, height) || !isValidBorder(border) || !isValidFormatAndType(format, type))
		return NULL;
	Mipmap* mip = new Mipmap(width, height, format, type);
	int size = mip->getImageSize();
	mip->m_pixels = new char[size];
	if (pixels)
		mip->upload((const char*)pixels, unpackAlignment);
	else
		memset(mip->m_pixels, 0, size);
	return mip;
}

void Mipmap::upload(const char* src, int unpackAlignment)
{
	char* dst = m_pixels;
	int dstRowLen = m_width * getBitsPerPixel() / 8;
	int srcRowLen = getAlignedRowLen(dstRowLen, unpackAlignment);
	for (int row = 0; row < m_height; ++row)
	{
		memcpy(dst, src, dstRowLen);
		dst += dstRowLen;
		src += srcRowLen;
	}
}

int Mipmap::getAlignedRowLen(int from, int unpackAlignment)
{
	int result = from;
	while (result % unpackAlignment != 0)
		++result;
	return result;
}

Mipmap* Mipmap::create_glCompressedTexImage2D(GLenum internalformat, GLsizei width, GLsizei height, GLint border,
	GLsizei imageSize, const GLvoid* data)
{
	if (!isValidCompressedFormat(internalformat))
	{
		LOGE("[%s] Invalid compressed format 0x%x", __FUNCTION__, internalformat);
		return NULL;
	}
	if (!isValidWidthHeight(width, height))
		return NULL;
	if (imageSize <= 0 || !data)
	{
		LOGE("[%s] Invalid imageSize %d or data 0x%p", __FUNCTION__, imageSize, data);
		return NULL;
	}
	Mipmap* mip = new Mipmap(width, height, internalformat, (GLenum)imageSize);
	mip->m_pixels = new char[imageSize];
	memcpy(mip->m_pixels, data, imageSize);
	return mip;
}

Mipmap* Mipmap::create_glTexStorage2D(GLenum internalformat, GLsizei width, GLsizei height)
{
	if (!isValidWidthHeight(width, height))
		return NULL;
	GLenum format;
	GLenum type = GL_UNSIGNED_BYTE;
	if (isValidCompressedFormat(internalformat))
	{
		format = internalformat;
		type = 16; // TODO
	}
	else if (internalformat != GL_RGBA8 && internalformat != GL_RGB8)
	{
		LOGE("[%s] Invalid or not support internalformat 0x%x", __FUNCTION__, internalformat);
		return NULL;
	}
	else
	{
		format = internalformat == GL_RGBA8 ? GL_RGBA : GL_RGB;
	}

	Mipmap* mip = new Mipmap(width, height, format, type);
	int size = mip->getImageSize();
	mip->m_pixels = new char[size];
	memset(mip->m_pixels, 0, size);
	return mip;
}

Mipmap* Mipmap::create_glCopyTexImage2D(GLenum internalformat, GLsizei width, GLsizei height, GLint border, const char* rgba)
{
	GLenum format;
	GLenum type = GL_UNSIGNED_BYTE;
	if (internalformat == GL_RGBA8)
		format = GL_RGBA;
	else if (internalformat == GL_RGB8)
		format = GL_RGB;
	else
		format = internalformat;

	if (format == GL_RGBA)
		return create_glTexImage2D(format, width, height, border, format, type, rgba, 1);
	
	int len;
	char* pixels = ImageHelper::convertTexFormatFromRgba(width, height, format, rgba, len);
	Mipmap* result = create_glTexImage2D(format, width, height, border, format, type, pixels, 1);
	SAFE_DEL(pixels);
	return result;
}

Mipmap* Mipmap::on_glTexSubImage2D(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type,
	const GLvoid* pixels, int unpackAlignment)
{
	if (!pixels)
	{
		LOGE("[%s] pixels == NULL", __FUNCTION__);
		return NULL;
	}
	if (isCompressed())
	{
		LOGE("[%s] This is a compressed mipmap", __FUNCTION__);
		return NULL;
	}
	if (!isValidWidthHeight(width, height) || !isValidFormatAndType(format, type))
		return NULL;
	if (xoffset < 0 || yoffset < 0)
	{
		LOGE("[%s] Negative values: xoffset = %d, yoffset = %d", __FUNCTION__, xoffset, yoffset);
		return NULL;
	}
	if (xoffset + width > m_width || yoffset + height > m_height)
	{
		LOGE("[%s] Too large region: xoffset=%d, width=%d, m_width=%d, yoffset=%d, height=%d, m_height=%d",
			__FUNCTION__, xoffset, width, m_width, yoffset, height, m_height);
		return NULL;
	}
	if (m_format != format)
	{
		LOGE("[%s] Formats are mismatched: old=0x%x, new=0x%x", __FUNCTION__, m_format, format);
		return NULL;
	}
	Mipmap* mip = create_glTexImage2D(0, width, height, 0, format, type, pixels, unpackAlignment);
	this->copySubMipmap(mip, xoffset, yoffset);
	return mip;
}

Mipmap* Mipmap::on_glCompressedTexSubImage2D(GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
	GLenum format, GLsizei imageSize, const GLvoid* data)
{
	if (!data)
	{
		LOGE("[%s] data == NULL", __FUNCTION__);
		return NULL;
	}
	if (!isCompressed())
	{
		LOGE("[%s] This is not a compressed mipmap", __FUNCTION__);
		return NULL;
	}
	if (!isValidWidthHeight(width, height))
		return NULL;
	if (xoffset < 0 || yoffset < 0)
	{
		LOGE("[%s] Negative values: xoffset = %d, yoffset = %d", __FUNCTION__, xoffset, yoffset);
		return NULL;
	}
	if (xoffset + width > m_width || yoffset + height > m_height)
	{
		LOGE("[%s] Too large region: xoffset=%d, width=%d, m_width=%d, yoffset=%d, height=%d, m_height=%d",
			__FUNCTION__, xoffset, width, m_width, yoffset, height, m_height);
		return NULL;
	}
	if (m_format != format)
	{
		LOGE("[%s] Formats are mismatched: old=0x%x, new=0x%x", __FUNCTION__, m_format, format);
		return NULL;
	}
	if (xoffset != 0 || yoffset != 0 || width != m_width || height != m_height)
	{
		LOGE("[%s] Not really support this function", __FUNCTION__);
		return NULL;
	}
	// TODO
	SAFE_DEL(m_pixels);
	m_type = imageSize;
	m_pixels = new char[imageSize];
	memcpy(m_pixels, data, imageSize);
	return this;
}

Mipmap* Mipmap::on_glCopyTexSubImage2D(GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height, const char* rgba)
{
	return on_glTexSubImage2D(xoffset, yoffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, rgba, 1);
}

void Mipmap::copySubMipmap(Mipmap* mip, int xoffset, int yoffset)
{
	int width = mip->m_width;
	int height = mip->m_height;
	int srcBytesPerPixel = mip->getBitsPerPixel() / 8;
	int dstBytesPerPixel = this->getBitsPerPixel() / 8;
	const u8* src = (const u8*)mip->m_pixels;
	GLenum srcType = mip->m_type;
	GLenum dstType = this->m_type;
	GLenum format = m_format;
	int srcRowLen = width * srcBytesPerPixel;
	for (int row = yoffset; row < yoffset + height; ++row)
	{
		// TODO: row order???
		//int r = height - 1 - row;
		int r = row;
		u8* dst = (u8*)m_pixels + (r * m_width + xoffset) * dstBytesPerPixel;
		if (srcType == dstType)
		{
			memcpy(dst, src, dstBytesPerPixel * width);
		}
		else
		{
			ImageHelper::copySubMipmapRow(width, format, srcType, dstType, srcBytesPerPixel, dstBytesPerPixel, dst, src);
		}
		src += srcRowLen;
	}
}

void Mipmap::copyRenderingRgba(int width, int height, const char* pixels)
{
	if (isCompressed())
	{
		LOGE("[%s] This mipmap is compressed", __FUNCTION__);
		return;
	}
	if (m_width != width || m_height != height)
	{
		LOGE("[%s] Widths/heights are mismatched m_width=%d, width=%d, m_height=%d, height=%d", __FUNCTION__, m_width, width, m_height, height);
		return;
	}
	if (m_type == GL_UNSIGNED_SHORT_5_6_5 || m_type == GL_UNSIGNED_BYTE)
	{
		if (m_type == GL_UNSIGNED_SHORT_5_6_5)
		{
			ImageHelper::convert_RGBA_to_565(width, height, pixels, m_pixels);
			return;
		}
		if (m_format == GL_RGB)
		{
			ImageHelper::convert_RGBA_to_RGB(width, height, pixels, m_pixels);
			return;
		}
		if (m_format == GL_RGBA)
		{
			memcpy(m_pixels, pixels, width * height * 4);
			return;
		}
	}
	LOGE("[%s] Invalid format 0x%x and type 0x%x", __FUNCTION__, m_format, m_type);
}

int Mipmap::getImageSize()
{
	return isCompressed() ? (int)m_type : m_width * m_height * getBitsPerPixel() / 8;
}

Mipmap::~Mipmap()
{
	SAFE_DEL(m_pixels);
}

Mipmap::Mipmap(int width, int height, GLenum format, GLenum type) :
	m_width(width),
	m_height(height),
	m_format(format),
	m_type(type),
	m_pixels(NULL)
{
}

bool Mipmap::isValidWidthHeight(int width, int height)
{
	if (width < 0 || height < 0)
	{
		LOGE("Invalid width %d, height %d", width, height);
		return false;
	}
	return true;
}

bool Mipmap::isValidBorder(int border)
{
	if (border != 0)
	{
		LOGE("Invalid border %d", border);
		return false;
	}
	return true;
}

bool Mipmap::isValidFormatAndType(GLenum format, GLenum type)
{
	bool ok = false;
	switch (format)
	{
	case GL_RGB:
		ok = type == GL_UNSIGNED_BYTE || type == GL_UNSIGNED_SHORT_5_6_5;
		break;
	case GL_RGBA:
		ok = type == GL_UNSIGNED_BYTE || type == GL_UNSIGNED_SHORT_4_4_4_4 || type == GL_UNSIGNED_SHORT_5_5_5_1;
		break;
	case GL_LUMINANCE_ALPHA:
	case GL_LUMINANCE:
	case GL_ALPHA:
		ok = type == GL_UNSIGNED_BYTE;
		break;
	}
	if (!ok)
	{
		LOGE("Invalid combination of format 0x%x and type 0x%x", format, type);
	}
	return ok;
}

int Mipmap::getBitsPerPixel()
{
	switch (m_format)
	{
		// PVRTC
	case GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
	case GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
		return 2;
	case GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
	case GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
		return 4;
		// ETC
	case GL_ETC1_RGB8_OES:
	case GL_COMPRESSED_RGB8_ETC2:
		return 4;
	case GL_COMPRESSED_RGBA8_ETC2_EAC:
		return 8;
		// DXT
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
		return 4;
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		return 8;
	}

	switch (m_type)
	{
	case GL_UNSIGNED_SHORT_4_4_4_4:
	case GL_UNSIGNED_SHORT_5_5_5_1:
	case GL_UNSIGNED_SHORT_5_6_5:
		return 16;

	case GL_UNSIGNED_BYTE:
	{
		switch (m_format)
		{
		case GL_RGBA:
			return 32;
		case GL_RGB:
			return 24;
		case GL_LUMINANCE_ALPHA:
			return 16;
		case GL_LUMINANCE:
		case GL_ALPHA:
			return 8;
		}
	}
	}
	LOGE("[%s] Should not go here: format=0x%x, type=0x%x", __FUNCTION__, m_format, m_type);
	return 0;
}

bool Mipmap::isCompressed()
{
	return isValidCompressedFormat(m_format);
}

bool Mipmap::isValidCompressedFormat(GLenum internalformat)
{
	return
		// PVR
		internalformat == GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG ||
		internalformat == GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG ||
		internalformat == GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG ||
		internalformat == GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG ||
		// ETC
		internalformat == GL_ETC1_RGB8_OES ||
		internalformat == GL_COMPRESSED_RGB8_ETC2 ||
		internalformat == GL_COMPRESSED_RGBA8_ETC2_EAC ||
		// DXT
		internalformat == GL_COMPRESSED_RGB_S3TC_DXT1_EXT ||
		internalformat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ||
		internalformat == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ||
		internalformat == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
}

bool Mipmap::isRawRgba()
{
	return m_type == GL_UNSIGNED_BYTE && m_format == GL_RGBA;
}

bool Mipmap::isRawRgb()
{
	return m_type == GL_UNSIGNED_BYTE && m_format == GL_RGB;
}

int Mipmap::getWidth() { return m_width; }
int Mipmap::getHeight() { return m_height; }
GLenum Mipmap::getFormat() { return m_format; }
GLenum Mipmap::getType() { return m_type; }
const char* Mipmap::getPixels() { return m_pixels; }

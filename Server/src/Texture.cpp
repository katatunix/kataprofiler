#include "Texture.h"
#include "log.h"

Texture::Texture() : Texture(0)
{
}

Texture::Texture(u32 id) : GlObject(id), m_texType(TEX_NONE)
{
	for (int i = 0; i < MAX_MIPMAP; ++i)
	{
		m_mipmaps[i] = NULL;
	}
}

Texture::~Texture()
{
	clearData();
}

void Texture::clearData()
{
	for (int i = 0; i < MAX_MIPMAP; ++i)
	{
		SAFE_DEL(m_mipmaps[i]);
	}
}

TextureType Texture::getTexType()
{
	return m_texType;
}

void Texture::setTexType(TextureType texType)
{
	m_texType = texType;
}

int Texture::numMipmaps()
{
	int num = 0;
	for (int i = 0; i < MAX_MIPMAP; ++i)
	{
		if (m_mipmaps[i]) ++num;
	}
	return num;
}

Mipmap* Texture::on_glTexImage2D(GLenum target, GLint level, GLint internalformat,
	GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type,
	const GLvoid* pixels, int unpackAlignment)
{
	if (!isValidTarget(target) || !isValidLevel(level))
		return NULL;
	SAFE_DEL(m_mipmaps[level]);
	m_mipmaps[level] = Mipmap::create_glTexImage2D(internalformat, width, height, border, format, type, pixels, unpackAlignment);
	return m_mipmaps[level];
}

Mipmap* Texture::on_glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height,
	GLint border, GLsizei imageSize, const GLvoid* data)
{
	if (!isValidTarget(target) || !isValidLevel(level))
		return NULL;
	SAFE_DEL(m_mipmaps[level]);
	m_mipmaps[level] = Mipmap::create_glCompressedTexImage2D(internalformat, width, height, border, imageSize, data);
	return m_mipmaps[level];
}

Mipmap* Texture::on_glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat,
	GLsizei width, GLsizei height, GLint border, const char* rgba)
{
	if (!isValidTarget(target) || !isValidLevel(level))
		return NULL;
	SAFE_DEL(m_mipmaps[level]);
	m_mipmaps[level] = Mipmap::create_glCopyTexImage2D(internalformat, width, height, border, rgba);
	return m_mipmaps[level];
}

bool Texture::on_glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	if (!isValidTarget(target))
		return false;
	if (levels <= 0 || !isValidLevel(levels - 1))
	{
		LOGE("[%s] Invalid levels %d", __FUNCTION__, levels);
		return false;
	}
	bool ok = true;
	for (int level = 0; level < levels; ++level)
	{
		SAFE_DEL(m_mipmaps[level]);
		m_mipmaps[level] = Mipmap::create_glTexStorage2D(internalformat, width, height);
		if (m_mipmaps[level] == NULL)
			ok = false;
		width = MAX(1, (width / 2));
		height = MAX(1, (height / 2));
	}
	return ok;
}

Mipmap* Texture::on_glTexSubImage2D(GLenum target, GLint level,
	GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
	GLenum format, GLenum type, const GLvoid* pixels, int unpackAlignment)
{
	if (!isValidTarget(target) || !isValidLevel(level) || !existsMipmap(level))
		return NULL;
	return m_mipmaps[level]->on_glTexSubImage2D(xoffset, yoffset, width, height, format, type, pixels, unpackAlignment);
}

Mipmap* Texture::on_glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
{
	if (!isValidTarget(target) || !isValidLevel(level))
		return NULL;
	
	if (m_mipmaps[level])
	{
		m_mipmaps[level]->on_glCompressedTexSubImage2D(xoffset, yoffset, width, height, format, imageSize, data);
		return m_mipmaps[level];
	}
	if (xoffset == 0 && yoffset == 0)
	{
		m_mipmaps[level] = Mipmap::create_glCompressedTexImage2D(format, width, height, 0, imageSize, data);
		return m_mipmaps[level];
	}
	LOGE("Mipmap with level %d does not exist", level);
	return NULL;
}

Mipmap* Texture::on_glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
	GLsizei width, GLsizei height, const char* rgba)
{
	if (!isValidTarget(target) || !isValidLevel(level) || !existsMipmap(level))
		return NULL;
	return m_mipmaps[level]->on_glCopyTexSubImage2D(xoffset, yoffset, width, height, rgba);
}

void Texture::copyRenderingRgba(int level, int width, int height, const char* pixels)
{
	if (!isValidLevel(level) || !existsMipmap(level)) return;
	m_mipmaps[level]->copyRenderingRgba(width, height, pixels);
}

Message* Texture::toMessage()
{
	Message* msg = new Message();
	msg->m_type = KMT_OBJECT_TEXTURE;

	int len = 4/*id*/ + 4/*texType*/ + 4/*mipmapCount*/;
	int mipmapCount = 0;
	for (int level = 0; level < MAX_MIPMAP; ++level)
	{
		if (m_mipmaps[level])
		{
			++mipmapCount;
			len += 4/*level*/ + 4/*width*/ + 4/*height*/ + 1/*isCompressed*/ + 4/*format*/ + 4/*type*/
				+ 1/*dummy*/ + m_mipmaps[level]->getImageSize();
		}
	}

	msg->m_length = len;
	msg->m_pData = new char[msg->m_length];
	char* buffer = msg->m_pData;
	memcpy(buffer, &m_id, 4);			buffer += 4;
	memcpy(buffer, &m_texType, 4);		buffer += 4;
	memcpy(buffer, &mipmapCount, 4);	buffer += 4;

	for (int level = 0; level < MAX_MIPMAP; ++level)
	{
		if (m_mipmaps[level])
		{
			Mipmap* mip = m_mipmaps[level];
			memcpy(buffer, &level, 4);			buffer += 4;
			int width = mip->getWidth();					memcpy(buffer, &width, 4);			buffer += 4;
			int height = mip->getHeight();					memcpy(buffer, &height, 4);			buffer += 4;
			u8 isCompressed = mip->isCompressed() ? 1 : 0;	memcpy(buffer, &isCompressed, 1);	buffer += 1;
			GLenum format = mip->getFormat();				memcpy(buffer, &format, 4);			buffer += 4;
			GLenum type = mip->getType();					memcpy(buffer, &type, 4);			buffer += 4;
			*buffer = 1;						buffer += 1;
			int imageSize = mip->getImageSize();
			memcpy(buffer, mip->getPixels(), imageSize);
			buffer += imageSize;
		}
	}
	return msg;
}

bool Texture::existsMipmap(int level)
{
	if (!m_mipmaps[level])
	{
		LOGE("Mipmap with level %d does not exist", level);
		return false;
	}
	return true;
}

bool Texture::isValidTarget(GLenum target)
{
	if (target != GL_TEXTURE_2D)
	{
		LOGE("Not supported target 0x%x, only GL_TEXTURE_2D (0x%x) is supported!", target, GL_TEXTURE_2D);
		return false;
	}
	return true;
}

bool Texture::isValidLevel(int level)
{
	if (level < 0 || level >= MAX_MIPMAP)
	{
		LOGE("Invalid level %d", level);
		return false;
	}
	return true;
}

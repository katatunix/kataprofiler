#include "ImageHelper.h"

namespace ImageHelper
{
	#define CONVERT(srcValue, srcBits, dstBits) ( (u16)(srcValue) * (u16)((1 << (dstBits)) - 1) / (u16)((1 << (srcBits)) - 1) )

	void convert_RGBA_to_RGB(int width, int height, const char* src, char* dst)
	{
		for (int i = 0; i < width * height; i++)
		{
			int j = i * 4;
			int k = i * 3;
			dst[k++] = src[j++];
			dst[k++] = src[j++];
			dst[k++] = src[j++];
		}
	}

	void convert_RGBA_to_565(int width, int height, const char* src, char* dst)
	{
		for (int i = 0; i < width * height; i++)
		{
			int j = i * 4;
			int k = i * 2;
			u16* dst16 = (u16*)(dst + k);
			*dst16 = (u16)CONVERT(src[j], 8, 5) << 11;
			*dst16 |= (u16)CONVERT(src[j + 1], 8, 6) << 5;
			*dst16 |= (u16)CONVERT(src[j + 2], 8, 5);
		}
	}

	void convert_RGBA_to_RGB(int width, int height, char* src)
	{
		for (int i = 0; i < width * height; i++)
		{
			int j = i * 4;
			int k = i * 3;
			src[k++] = src[j++];
			src[k++] = src[j++];
			src[k++] = src[j++];
		}
	}

	void swapRB(char* buffer, int pixelsNumber, bool hasAlpha/* = true*/)
	{
		const int k_bytesPerPixel = hasAlpha ? 4 : 3;
		const int k_bytesTotal = k_bytesPerPixel * pixelsNumber;
		char tmp;
		for (int i = 0; i < k_bytesTotal; i += k_bytesPerPixel)
		{
			tmp = buffer[i];
			buffer[i] = buffer[i + 2];
			buffer[i + 2] = tmp;
		}
	}

	void copySubMipmapRow(int width, GLenum format, GLenum srcType, GLenum dstType,
		int srcBytesPerPixel, int dstBytesPerPixel, u8* dst, const u8* src)
	{
		for (int i = 0; i < width; ++i)
		{
			if (format == GL_RGBA)
			{
				if (srcType == GL_UNSIGNED_BYTE && dstType == GL_UNSIGNED_SHORT_4_4_4_4)
				{
					u16* dst16 = (u16*)dst;
					*dst16 = (u16)CONVERT(src[0], 8, 4) << 12;
					*dst16 |= (u16)CONVERT(src[1], 8, 4) << 8;
					*dst16 |= (u16)CONVERT(src[2], 8, 4) << 4;
					*dst16 |= (u16)CONVERT(src[3], 8, 4);
				}
				else if (srcType == GL_UNSIGNED_BYTE && dstType == GL_UNSIGNED_SHORT_5_5_5_1)
				{
					u16* dst16 = (u16*)dst;
					*dst16 = (u16)CONVERT(src[0], 8, 5) << 11;
					*dst16 |= (u16)CONVERT(src[1], 8, 5) << 6;
					*dst16 |= (u16)CONVERT(src[2], 8, 5) << 1;
					*dst16 |= (u16)CONVERT(src[3], 8, 1);
				}

				else if (srcType == GL_UNSIGNED_SHORT_4_4_4_4 && dstType == GL_UNSIGNED_BYTE)
				{
					u16 src16 = *((u16*)src);
					dst[0] = (u8)CONVERT((src16 >> 12) & 0xF, 4, 8);
					dst[1] = (u8)CONVERT((src16 >> 8) & 0xF, 4, 8);
					dst[2] = (u8)CONVERT((src16 >> 4) & 0xF, 4, 8);
					dst[3] = (u8)CONVERT((src16) & 0xF, 4, 8);
				}
				else if (srcType == GL_UNSIGNED_SHORT_4_4_4_4 && dstType == GL_UNSIGNED_SHORT_5_5_5_1)
				{
					u16 src16 = *((u16*)src);
					u16* dst16 = (u16*)dst;
					*dst16 = (u16)CONVERT((src16 >> 12) & 0xF, 4, 5) << 11;
					*dst16 |= (u16)CONVERT((src16 >> 8) & 0xF, 4, 5) << 6;
					*dst16 |= (u16)CONVERT((src16 >> 4) & 0xF, 4, 5) << 1;
					*dst16 |= (u16)CONVERT((src16) & 0xF, 4, 1);
				}

				else if (srcType == GL_UNSIGNED_SHORT_5_5_5_1 && dstType == GL_UNSIGNED_BYTE)
				{
					u16 src16 = *((u16*)src);
					dst[0] = (u8)CONVERT((src16 >> 11) & 0x1F, 5, 8);
					dst[1] = (u8)CONVERT((src16 >> 6) & 0x1F, 5, 8);
					dst[2] = (u8)CONVERT((src16 >> 1) & 0x1F, 5, 8);
					dst[3] = (u8)CONVERT((src16) & 0x01, 1, 8);
				}
				else if (srcType == GL_UNSIGNED_SHORT_5_5_5_1 && dstType == GL_UNSIGNED_SHORT_4_4_4_4)
				{
					u16 src16 = *((u16*)src);
					u16* dst16 = (u16*)dst;
					*dst16 = (u16)CONVERT((src16 >> 11) & 0x1F, 5, 4) << 12;
					*dst16 |= (u16)CONVERT((src16 >> 6) & 0x1F, 5, 4) << 8;
					*dst16 |= (u16)CONVERT((src16 >> 1) & 0x1F, 5, 4) << 4;
					*dst16 |= (u16)CONVERT((src16) & 0x01, 1, 4);
				}
			}
			else if (format == GL_RGB)
			{
				if (srcType == GL_UNSIGNED_BYTE && dstType == GL_UNSIGNED_SHORT_5_6_5)
				{
					u16* dst16 = (u16*)dst;
					*dst16 = (u16)CONVERT(src[0], 8, 5) << 11;
					*dst16 |= (u16)CONVERT(src[1], 8, 6) << 5;
					*dst16 |= (u16)CONVERT(src[2], 8, 5);
				}
				else if (srcType == GL_UNSIGNED_SHORT_5_6_5 && dstType == GL_UNSIGNED_BYTE)
				{
					u16 src16 = *((u16*)src);
					dst[0] = (u8)CONVERT((src16 >> 11) & 0x1F, 5, 8);
					dst[1] = (u8)CONVERT((src16 >> 5) & 0x3F, 6, 8);
					dst[2] = (u8)CONVERT((src16) & 0x1F, 5, 8);
				}
			}
			else
			{
				// something went wrong
			}
			src += srcBytesPerPixel;
			dst += dstBytesPerPixel;
		}
	}

	char* convertTexFormatFromRgba(int width, int height, GLenum format, const char* pixels, int& pixelsLen)
	{
		char* newPixels = NULL;

		switch (format)
		{
		case GL_RGB:
		{
			pixelsLen = width * height * 3;

			if (pixelsLen > 0 && pixels)
			{
				newPixels = new char[pixelsLen];

				for (int i = 0; i < width * height; i++)
				{
					int j = i * 4;
					int k = i * 3;
					newPixels[k++] = pixels[j++];
					newPixels[k++] = pixels[j++];
					newPixels[k++] = pixels[j++];
				}
			}

			break;
		}
		case GL_ALPHA:
		{
			pixelsLen = width * height * 1;

			if (pixelsLen > 0 && pixels)
			{
				newPixels = new char[pixelsLen];

				for (int i = 0; i < width * height; i++)
				{
					int j = i * 4;
					int k = i * 1;
					newPixels[k] = pixels[j + 3];
				}
			}

			break;
		}
		case GL_LUMINANCE:
		{
			pixelsLen = width * height * 1;

			if (pixelsLen > 0 && pixels)
			{
				newPixels = new char[pixelsLen];
				for (int i = 0; i < width * height; i++)
				{
					int j = i * 4;
					int k = i * 1;
					newPixels[k] = (char)(
						(int)(pixels[j] + pixels[j + 1] + pixels[j + 2]) / 3
						);
				}
			}

			break;
		}
		case GL_LUMINANCE_ALPHA:
		{
			pixelsLen = width * height * 2;

			if (pixelsLen > 0 && pixels)
			{
				newPixels = new char[pixelsLen];

				for (int i = 0; i < width * height; i++)
				{
					int j = i * 4;
					int k = i * 2;
					newPixels[k] = (char)(
						(int)(pixels[j] + pixels[j + 1] + pixels[j + 2]) / 3
						);
					newPixels[k + 1] = pixels[j + 3];
				}
			}

			break;
		}
		}

		return newPixels;
	}

	int makeTgaHeader(char* _buffer, s16 width, s16 height, bool hasAlpha/* = true*/)
	{
		const u8		cGarbage = 0;
		const s16		iGarbage = 0;
		const u8		pixelDepth = hasAlpha ? 32 : 24;
		const u8		type = 2;

		char* buffer = _buffer;

		memcpy(buffer, &cGarbage, 1);		buffer++;
		memcpy(buffer, &cGarbage, 1);		buffer++;

		memcpy(buffer, &type, 1);			buffer++;

		memcpy(buffer, &iGarbage, 2);		buffer += 2;
		memcpy(buffer, &iGarbage, 2);		buffer += 2;
		memcpy(buffer, &cGarbage, 1);		buffer++;
		memcpy(buffer, &iGarbage, 2);		buffer += 2;
		memcpy(buffer, &iGarbage, 2);		buffer += 2;

		memcpy(buffer, &width, 2);			buffer += 2;
		memcpy(buffer, &height, 2);			buffer += 2;
		memcpy(buffer, &pixelDepth, 1);		buffer++;

		memcpy(buffer, &cGarbage, 1);		buffer++;

		return (int)(buffer - _buffer);
	}

	void convertToTga(char* buffer, int width, int height, bool hasAlpha/* = true*/)
	{
		const int bytesPerPixel = hasAlpha ? 4 : 3;
		const int total = width * height * bytesPerPixel;
		char tmp;
		for (int i = 0; i < total; i += bytesPerPixel)
		{
			tmp = buffer[i];
			buffer[i] = buffer[i + 2];
			buffer[i + 2] = tmp;
		}
	}

	char* polishScreenshot(const char* rgba, int width, int height, bool allowScale, bool allowSwapRB,
		int& widthScaled, int& heightScaled, int& len)
	{
		const int k_bytesPerPixel_actual = 3; // RGB
		len = width * height * k_bytesPerPixel_actual;

		// Remove alpha to have RGB
		char* buffer = new char[len];
		convert_RGBA_to_RGB(width, height, rgba, buffer);

		const int k_maxSize = 2 * 1024 * 1024; // 2 MB
		widthScaled = width;	// ***
		heightScaled = height;	// ***
		int zoomLevel = 1;

		if (allowScale)
		{
			while ((widthScaled > 1 && heightScaled > 1) && (widthScaled * heightScaled * k_bytesPerPixel_actual > k_maxSize))
			{
				widthScaled = widthScaled >> 1; // ***
				heightScaled = heightScaled >> 1; // ***
				zoomLevel = zoomLevel << 1;
			}
		}

		if (zoomLevel > 1)
		{
			len = widthScaled * heightScaled * k_bytesPerPixel_actual; // ***
			char* bufferScaled = new char[len];

			for (int x = 0; x < widthScaled; x++)
			{
				for (int y = 0; y < heightScaled; y++)
				{
					int offset = (y * widthScaled + x) * k_bytesPerPixel_actual;

					int x2 = x * zoomLevel;
					int y2 = y * zoomLevel;
					int offset2 = (y2 * width + x2) * k_bytesPerPixel_actual;

					memcpy(bufferScaled + offset, buffer + offset2, k_bytesPerPixel_actual);
					/*for (int i = 0; i < k_bytesPerPixel_actual; i++)
					{
					bufferScaled[offset + i] = buffer[offset2 + i];
					}*/

				}
			}

			delete[] buffer;
			buffer = bufferScaled;
		}

		if (allowSwapRB)
		{
			swapRB(buffer, widthScaled * heightScaled, false);
		}

		return buffer;
	}
}

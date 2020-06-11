#pragma once

#include "common.h"
#include "glDefine.h"

namespace ImageHelper
{
	void convert_RGBA_to_RGB(int width, int height, const char* src, char* dst);
	void convert_RGBA_to_565(int width, int height, const char* src, char* dst);
	void convert_RGBA_to_RGB(int width, int height, char* src);
	
	void swapRB(char* buffer, int pixelsNumber, bool hasAlpha = true);
	
	void copySubMipmapRow(int width, GLenum format, GLenum srcType, GLenum dstType,
		int srcBytesPerPixel, int dstBytesPerPixel, u8* dst, const u8* src);
	
	char* convertTexFormatFromRgba(int width, int height, GLenum internalformat, const char* pixels, int& pixelsLen);
	
	int makeTgaHeader(char* buffer, s16 width, s16 height, bool hasAlpha = true);
	void convertToTga(char* buffer, int width, int height, bool hasAlpha = true);

	char* polishScreenshot(const char* rgba, int width, int height, bool allowScale, bool allowSwapRB,
		int& widthScaled, int& heightScaled, int& len);
}

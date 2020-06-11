// This is the main DLL file.

#include "stdafx.h"

#include "TexDecomp.h"

#include "PVRTDecompress.h"
#include "ETCDecompress.h"
#include "ETC2Decompress.h"
#include "DXTDecompress.h"

namespace TexDecomp {

void Class1::Decompress_PVRTC(unsigned char* pCompressedData,
				int Do2bitMode,
				int XDim,
				int YDim,
				unsigned char* pResultImage,
				int isSwapRB)
{
	PVRTDecompressPVRTC(
		pCompressedData,
		Do2bitMode,
		XDim,
		YDim,
		pResultImage);
	if (isSwapRB)
	{
		swapRB(pResultImage, XDim * YDim, true);
	}
}

void Class1::Decompress_ETC( unsigned char* rgba, unsigned char* blocks, int width, int height, int isSwapRB)
{
	DecompressImageETC( rgba, blocks, width, height );
	if (isSwapRB)
	{
		swapRB(rgba, width * height, true);
	}
}

void Class1::Decompress_ETC2(unsigned int srcFormat, unsigned char* rgba, unsigned char* blocks, int width, int height, int isSwapRB)
{
	DecompressImageETC2( srcFormat, rgba, blocks, width, height );
	if (isSwapRB)
	{
		swapRB(rgba, width * height, true);
	}
}

void Class1::Decompress_DXT(int dxtType, unsigned char* rgba, unsigned char* blocks, int width, int height, int isSwapRB)
{
	switch (dxtType)
	{
	case 1:
		DecompressImageDXT(rgba, blocks, width, height, CF_DXT1);
		break;
	case 3:
		DecompressImageDXT(rgba, blocks, width, height, CF_DXT3);
		break;
	case 5:
		DecompressImageDXT(rgba, blocks, width, height, CF_DXT5);
		break;
	}

	if (isSwapRB)
	{
		swapRB(rgba, width * height, true);
	}
}

void Class1::swapRB(unsigned char* buffer, int pixelsNumber, bool hasAlpha)
{
	const int k_bytesPerPixel = hasAlpha ? 4 : 3;
	const int k_bytesTotal = k_bytesPerPixel * pixelsNumber;
	unsigned char tmp;
	for (int i = 0; i < k_bytesTotal; i += k_bytesPerPixel)
	{
		tmp = buffer[i];
		buffer[i] = buffer[i + 2];
		buffer[i + 2] = tmp;
	}
}

} // namespace TexDecomp

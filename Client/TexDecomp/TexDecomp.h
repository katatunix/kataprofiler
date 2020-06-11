// TexDecomp.h

#pragma once

using namespace System;

namespace TexDecomp {

	public ref class Class1
	{
	public:
		static void Decompress_PVRTC(unsigned char* pCompressedData,
				int Do2bitMode,
				int XDim,
				int YDim,
				unsigned char* pResultImage,
				int isSwapRB);

		static void Decompress_ETC( unsigned char* rgba, unsigned char* blocks,
			int width, int height, int isSwapRB);

		static void Decompress_ETC2( unsigned int srcFormat, unsigned char* rgba, unsigned char* blocks,
			int width, int height, int isSwapRB);

		static void Decompress_DXT(int dxtType, unsigned char* rgba, unsigned char* blocks,
			int width, int height, int isSwapRB);

	private:
		static void swapRB(unsigned char* buffer, int pixelsNumber, bool hasAlpha);
	};
}

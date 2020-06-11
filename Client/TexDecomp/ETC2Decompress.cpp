#include "StdAfx.h"
#include "ETC2Decompress.h"

#define GL_ETC1_RGB8_OES				0x8D64

#define GL_COMPRESSED_R11_EAC                            0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC                     0x9271
#define GL_COMPRESSED_RG11_EAC                           0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC                    0x9273
#define GL_COMPRESSED_RGB8_ETC2                          0x9274
#define GL_COMPRESSED_SRGB8_ETC2                         0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2      0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2     0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC                     0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC				 0x9279

typedef unsigned char GLubyte;

typedef unsigned int uint;
typedef unsigned char uint8;

typedef unsigned int khronos_uint32_t;

extern void decompressBlockETC2c(uint block_part1, uint block_part2, uint8* img,
								 int width, int height, int startx, int starty, int channels);
extern void decompressBlockETC21BitAlphaC(uint block_part1, uint block_part2, uint8* img, uint8* alphaimg,
										  int width, int height, int startx, int starty, int channels);
extern void decompressBlockAlphaC(uint8* data, uint8* img,
								  int width, int height, int startx, int starty, int channels);
extern void decompressBlockAlpha16bitC(uint8* data, uint8* img,
									   int width, int height, int startx, int starty, int channels);

extern void setupAlphaTable();

// This global variable affects the behaviour of decompressBlockAlpha16bitC.
extern int formatSigned;

static void readBigEndian4byteWord(khronos_uint32_t* pBlock, const GLubyte *s)
{
	*pBlock = (s[0] << 24) | (s[1] << 16) | (s[2] << 8) | s[3];
}

void DecompressImageETC2( unsigned int srcFormat, unsigned char* dstImage, const void* srcBlocks, int activeWidth, int activeHeight )
{
	unsigned int width, height;
	unsigned int block_part1, block_part2;
	unsigned int x, y;
	/*const*/ GLubyte* src = (GLubyte*)srcBlocks;
	// AF_11BIT is used to compress R11 & RG11 though its not alpha data.
	enum {AF_NONE, AF_1BIT, AF_8BIT, AF_11BIT} alphaFormat = AF_NONE;
	int dstChannels, dstChannelBytes;

	switch (srcFormat)
	{
	  case GL_ETC1_RGB8_OES:
	  case GL_COMPRESSED_RGB8_ETC2:
	    dstChannelBytes = sizeof(GLubyte);
		dstChannels = 3;
        break;

	  case GL_COMPRESSED_RGBA8_ETC2_EAC:
	    dstChannelBytes = sizeof(GLubyte);
		dstChannels = 4;
	    alphaFormat = AF_8BIT;
		break;

	  case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
	    dstChannelBytes = sizeof(GLubyte);
		dstChannels = 4;
		alphaFormat = AF_1BIT;
        break;

	  case GL_COMPRESSED_SRGB8_ETC2:
			dstChannelBytes = sizeof(GLubyte);
			dstChannels = 3;
        break;

	  case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
			dstChannelBytes = sizeof(GLubyte);
			dstChannels = 4;
			alphaFormat = AF_8BIT;
		break;

	  case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
			dstChannelBytes = sizeof(GLubyte);
			dstChannels = 4;
			alphaFormat = AF_1BIT;
        break;

	  default:
	    return;//assert here
	}

    /* active_{width,height} show how many pixels contain active data,
	 * (the rest are just for making sure we have a 2*a x 4*b size).
	 */

	/* Compute the full width & height. */
	width = ((activeWidth+3)/4)*4;
	height = ((activeHeight+3)/4)*4;

	/* printf("Width = %d, Height = %d\n", width, height); */
	/* printf("active pixel area: top left %d x %d area.\n", activeWidth, activeHeight); */
	
	if (alphaFormat != AF_NONE)
		setupAlphaTable();

	// NOTE: none of the decompress functions actually use the <height> parameter
	if (alphaFormat == AF_11BIT) {
		// One or two 11-bit alpha channels for R or RG.
		for (y=0; y < height/4; y++) {
			for (x=0; x < width/4; x++) {
				decompressBlockAlpha16bitC(src, dstImage, width, height, 4*x, 4*y, dstChannels);
				src += 8;
				if (srcFormat == GL_COMPRESSED_RG11_EAC || srcFormat == GL_COMPRESSED_SIGNED_RG11_EAC) {
					decompressBlockAlpha16bitC(src, dstImage + dstChannelBytes, width, height, 4*x, 4*y, dstChannels);
					src += 8;
				}
			}
		}
	} else {
		for (y=0; y < height/4; y++) {
			for (x=0; x < width/4; x++) {
				// Decode alpha channel for RGBA
				if (alphaFormat == AF_8BIT) {
					decompressBlockAlphaC(src, dstImage + 3, width, height, 4*x, 4*y, dstChannels);
					src += 8;
				}
				// Decode color dstChannels
				readBigEndian4byteWord(&block_part1, src);
				src += 4;
				readBigEndian4byteWord(&block_part2, src);
				src += 4;
				if (alphaFormat == AF_1BIT)
				    decompressBlockETC21BitAlphaC(block_part1, block_part2, dstImage, 0, width, height, 4*x, 4*y, dstChannels);
				else
				    decompressBlockETC2c(block_part1, block_part2, dstImage, width, height, 4*x, 4*y, dstChannels);
			}
		}
	}

	if (dstChannels == 3)
	{
		for (int i = width * height - 1; i >= 0; i--)
		{
			int j = i * 4 + 3;
			int k = i * 3 + 2;

			dstImage[j] = 0xFF;
			dstImage[j - 1] = dstImage[k];
			dstImage[j - 2] = dstImage[k - 1];
			dstImage[j - 3] = dstImage[k - 2];
		}
	}
}

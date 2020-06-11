#include "StdAfx.h"
#include "ETCDecompress.h"


#define _CLAMP_(X,Xmin,Xmax) ( (X)<(Xmax) ? ( (X)<(Xmin)?(Xmin):(X) ) : (Xmax) )

unsigned int ETC_FLIP =  0x01000000;
unsigned int ETC_DIFF = 0x02000000;
const int mod[8][4]={{2, 8,-2,-8},
                    {5, 17, -5, -17},
                    {9, 29, -9, -29},
                    {13, 42, -13, -42},
                    {18, 60, -18, -60},
                    {24, 80, -24, -80},
                    {33, 106, -33, -106},
                    {47, 183, -47, -183}};

// lsb: hgfedcba ponmlkji msb: hgfedcba ponmlkji due to endianness
static unsigned long ModifyPixel(int red, int green, int blue, int x, int y, unsigned long modBlock, int modTable)
{
    int index = x*4+y, pixelMod;
    unsigned long mostSig = modBlock<<1;
    if (index<8)    //hgfedcba
        pixelMod = mod[modTable][((modBlock>>(index+24))&0x1)+((mostSig>>(index+8))&0x2)];
    else    // ponmlkj
        pixelMod = mod[modTable][((modBlock>>(index+8))&0x1)+((mostSig>>(index-8))&0x2)];
    
    red = _CLAMP_(red+pixelMod,0,255);
    green = _CLAMP_(green+pixelMod,0,255);
    blue = _CLAMP_(blue+pixelMod,0,255);
    
    return ((blue<<16) + (green<<8) + red)|0xff000000;
}

static void DecompressETC(unsigned char* pDestData, const void* pSrcData)
{
    unsigned long blockTop, blockBot, *input = (unsigned long*)pSrcData, *output;
    unsigned char red1, green1, blue1, red2, green2, blue2;
    bool bFlip, bDiff;
    int modtable1,modtable2;
    
    blockTop = *(input++);
    blockBot = *(input++);
    
    output = (unsigned long*)pDestData;
    // check flipbit
    bFlip = (blockTop & ETC_FLIP) != 0;
    bDiff = (blockTop & ETC_DIFF) != 0;
    
    if(bDiff)
    {    // differential mode 5 colour bits + 3 difference bits
        // get base colour for subblock 1
        blue1 = (unsigned char)((blockTop&0xf80000)>>16);
        green1 = (unsigned char)((blockTop&0xf800)>>8);
        red1 = (unsigned char)(blockTop&0xf8);
        
        // get differential colour for subblock 2
        signed char blues = (signed char)(blue1>>3) + ((signed char) ((blockTop & 0x70000) >> 11)>>5);
        signed char greens = (signed char)(green1>>3) + ((signed char)((blockTop & 0x700) >>3)>>5);
        signed char reds = (signed char)(red1>>3) + ((signed char)((blockTop & 0x7)<<5)>>5);
        
        blue2 = (unsigned char)blues;
        green2 = (unsigned char)greens;
        red2 = (unsigned char)reds;
        
        red1 = red1 +(red1>>5);    // copy bits to lower sig
        green1 = green1 + (green1>>5);    // copy bits to lower sig
        blue1 = blue1 + (blue1>>5);    // copy bits to lower sig
        
        red2 = (red2<<3) +(red2>>2);    // copy bits to lower sig
        green2 = (green2<<3) + (green2>>2);    // copy bits to lower sig
        blue2 = (blue2<<3) + (blue2>>2);    // copy bits to lower sig
    }
    else
    {    // individual mode 4 + 4 colour bits
        // get base colour for subblock 1
        blue1 = (unsigned char)((blockTop&0xf00000)>>16);
        blue1 = blue1 +(blue1>>4);    // copy bits to lower sig
        green1 = (unsigned char)((blockTop&0xf000)>>8);
        green1 = green1 + (green1>>4);    // copy bits to lower sig
        red1 = (unsigned char)(blockTop&0xf0);
        red1 = red1 + (red1>>4);    // copy bits to lower sig
        
        // get base colour for subblock 2
        blue2 = (unsigned char)((blockTop&0xf0000)>>12);
        blue2 = blue2 +(blue2>>4);    // copy bits to lower sig
        green2 = (unsigned char)((blockTop&0xf00)>>4);
        green2 = green2 + (green2>>4);    // copy bits to lower sig
        red2 = (unsigned char)((blockTop&0xf)<<4);
        red2 = red2 + (red2>>4);    // copy bits to lower sig
    }
    // get the modtables for each subblock
    modtable1 = (blockTop>>29)&0x7; 
    modtable2 = (blockTop>>26)&0x7; 
    
    if(!bFlip)
    {   // 2 2x4 blocks side by side
        for(int j=0;j<4;j++)    // vertical
        {
            for(int k=0;k<2;k++)    // horizontal
            {
                *(output+j*4+k) = ModifyPixel(red1,green1,blue1,k,j,blockBot,modtable1);
                *(output+j*4+k+2) = ModifyPixel(red2,green2,blue2,k+2,j,blockBot,modtable2);
            }
        }
    }
    else
    {   // 2 4x2 blocks on top of each other
        for(int j=0;j<2;j++)
        {
            for(int k=0;k<4;k++)
            {
                *(output+j*4+k) = ModifyPixel(red1,green1,blue1,k,j,blockBot,modtable1);
                *(output+(j+2)*4+k) = ModifyPixel(red2,green2,blue2,k,j+2,blockBot,modtable2);
            }
        }
    }
}

void DecompressImageETC( unsigned char* rgba, const void* blocks, int width, int height )
{
    // initialise the block input
    unsigned char const* sourceBlock = reinterpret_cast< unsigned char const* >( blocks );
    int bytesPerBlock = 8;
    
    // loop over blocks
    for( int y = 0; y < height; y += 4 )
    {
        for( int x = 0; x < width; x += 4 )
        {
            // decompress the block
            unsigned char targetRgba[4*16];
            DecompressETC( targetRgba, sourceBlock );
            
            // write the decompressed pixels to the correct image locations
            unsigned char const* sourcePixel = targetRgba;
            for( int py = 0; py < 4; ++py )
            {
                for( int px = 0; px < 4; ++px )
                {
                    // get the target location
                    int sx = x + px;
                    int sy = y + py;
                    if( sx < width && sy < height )
                    {
                        unsigned char* targetPixel = rgba + 4*( width*sy + sx );
                        
                        // copy the rgba value
                        for( int i = 0; i < 4; ++i )
                            *targetPixel++ = *sourcePixel++;
                    }
                    else
                    {
                        // skip this pixel as its outside the image
                        sourcePixel += 4;
                    }
                }
            }
            
            // advance
            sourceBlock += bytesPerBlock;
        }
    }
}

#include "StdAfx.h"
#include "DXTDecompress.h"

// DXT decompression based on the Squish library, modified for Urho3D

/* -----------------------------------------------------------------------------

    Copyright (c) 2006 Simon Brown                          si@sjbrown.co.uk

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the 
    "Software"), to    deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to 
    permit persons to whom the Software is furnished to do so, subject to 
    the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
   -------------------------------------------------------------------------- */

static int Unpack565( unsigned char const* packed, unsigned char* colour )
{
    // build the packed value
    int value = ( int )packed[0] | ( ( int )packed[1] << 8 );
    
    // get the components in the stored range
    unsigned char red = ( unsigned char )( ( value >> 11 ) & 0x1f );
    unsigned char green = ( unsigned char )( ( value >> 5 ) & 0x3f );
    unsigned char blue = ( unsigned char )( value & 0x1f );
    
    // scale up to 8 bits
    colour[0] = ( red << 3 ) | ( red >> 2 );
    colour[1] = ( green << 2 ) | ( green >> 4 );
    colour[2] = ( blue << 3 ) | ( blue >> 2 );
    colour[3] = 255;
    
    // return the value
    return value;
}

static void DecompressColourDXT( unsigned char* rgba, void const* block, bool isDxt1 )
{
    // get the block bytes
    unsigned char const* bytes = reinterpret_cast< unsigned char const* >( block );
    
    // unpack the endpoints
    unsigned char codes[16];
    int a = Unpack565( bytes, codes );
    int b = Unpack565( bytes + 2, codes + 4 );
    
    // generate the midpoints
    for( int i = 0; i < 3; ++i )
    {
        int c = codes[i];
        int d = codes[4 + i];

        if( isDxt1 && a <= b )
        {
            codes[8 + i] = ( unsigned char )( ( c + d )/2 );
            codes[12 + i] = 0;
        }
        else
        {
            codes[8 + i] = ( unsigned char )( ( 2*c + d )/3 );
            codes[12 + i] = ( unsigned char )( ( c + 2*d )/3 );
        }
    }
    
    // fill in alpha for the intermediate values
    codes[8 + 3] = 255;
    codes[12 + 3] = ( isDxt1 && a <= b ) ? 0 : 255;
    
    // unpack the indices
    unsigned char indices[16];
    for( int i = 0; i < 4; ++i )
    {
        unsigned char* ind = indices + 4*i;
        unsigned char packed = bytes[4 + i];
        
        ind[0] = packed & 0x3;
        ind[1] = ( packed >> 2 ) & 0x3;
        ind[2] = ( packed >> 4 ) & 0x3;
        ind[3] = ( packed >> 6 ) & 0x3;
    }
    
    // store out the colours
    for( int i = 0; i < 16; ++i )
    {
        unsigned char offset = 4*indices[i];
        for( int j = 0; j < 4; ++j )
            rgba[4*i + j] = codes[offset + j];
    }
}

static void DecompressAlphaDXT3( unsigned char* rgba, void const* block )
{
    unsigned char const* bytes = reinterpret_cast< unsigned char const* >( block );
    
    // unpack the alpha values pairwise
    for( int i = 0; i < 8; ++i )
    {
        // quantise down to 4 bits
        unsigned char quant = bytes[i];
        
        // unpack the values
        unsigned char lo = quant & 0x0f;
        unsigned char hi = quant & 0xf0;
        
        // convert back up to bytes
        rgba[8*i + 3] = lo | ( lo << 4 );
        rgba[8*i + 7] = hi | ( hi >> 4 );
    }
}

static void DecompressAlphaDXT5( unsigned char* rgba, void const* block )
{
    // get the two alpha values
    unsigned char const* bytes = reinterpret_cast< unsigned char const* >( block );
    int alpha0 = bytes[0];
    int alpha1 = bytes[1];
    
    // compare the values to build the codebook
    unsigned char codes[8];
    codes[0] = ( unsigned char )alpha0;
    codes[1] = ( unsigned char )alpha1;
    if( alpha0 <= alpha1 )
    {
        // use 5-alpha codebook
        for( int i = 1; i < 5; ++i )
            codes[1 + i] = ( unsigned char )( ( ( 5 - i )*alpha0 + i*alpha1 )/5 );
        codes[6] = 0;
        codes[7] = 255;
    }
    else
    {
        // use 7-alpha codebook
        for( int i = 1; i < 7; ++i )
            codes[1 + i] = ( unsigned char )( ( ( 7 - i )*alpha0 + i*alpha1 )/7 );
    }
    
    // decode the indices
    unsigned char indices[16];
    unsigned char const* src = bytes + 2;
    unsigned char* dest = indices;
    for( int i = 0; i < 2; ++i )
    {
        // grab 3 bytes
        int value = 0;
        for( int j = 0; j < 3; ++j )
        {
            int byte = *src++;
            value |= ( byte << 8*j );
        }
        
        // unpack 8 3-bit values from it
        for( int j = 0; j < 8; ++j )
        {
            int index = ( value >> 3*j ) & 0x7;
            *dest++ = ( unsigned char )index;
        }
    }
    
    // write out the indexed codebook values
    for( int i = 0; i < 16; ++i )
        rgba[4*i + 3] = codes[indices[i]];
}

static void DecompressDXT( unsigned char* rgba, const void* block, CompressedFormat format)
{
    // get the block locations
    void const* colourBlock = block;
    void const* alphaBock = block;
    if( format == CF_DXT3 || format == CF_DXT5)
        colourBlock = reinterpret_cast< unsigned char const* >( block ) + 8;
    
    // decompress colour
    DecompressColourDXT( rgba, colourBlock, format == CF_DXT1 );
    
    // decompress alpha separately if necessary
    if( format == CF_DXT3 )
        DecompressAlphaDXT3( rgba, alphaBock );
    else if ( format == CF_DXT5 )
        DecompressAlphaDXT5( rgba, alphaBock );
}

void DecompressImageDXT( unsigned char* rgba, const void* blocks, int width, int height, CompressedFormat format )
{
    // initialise the block input
    unsigned char const* sourceBlock = reinterpret_cast< unsigned char const* >( blocks );
    int bytesPerBlock = format == CF_DXT1 ? 8 : 16;
    
    // loop over blocks
    for( int y = 0; y < height; y += 4 )
    {
        for( int x = 0; x < width; x += 4 )
        {
            // decompress the block
            unsigned char targetRgba[4*16];
            DecompressDXT( targetRgba, sourceBlock, format );
            
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

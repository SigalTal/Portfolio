/********************************
 * Reviewer: Sivan 
 * Author: Sigal Tal		
 * File: bit_array.h
 * *****************************/
#include <stdio.h>/*printf*/
#include <limits.h>/*CHAR_BIT*/
#include <assert.h>
#include "bit_array.h"

static char lut_bits_on_in_nibble[16]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
static char lut_mirror_nibble[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};

bit_array_t BitArraySetAll(bit_array_t ba)
{
    ba|=(bit_array_t)~(0);

    return ba;
}

bit_array_t BitArrayResetAll(bit_array_t ba)
{
    ba&=(bit_array_t)0;

    return ba;
}

bit_array_t BitArraySetOn(bit_array_t ba, size_t index)
{
    bit_array_t set_bit=1;

    set_bit<<=index;

    return ba|set_bit;
}

bit_array_t BitArraySetOff(bit_array_t ba, size_t index)
{
    bit_array_t set_off_bit=(size_t)1;

    set_off_bit<<=index;

    return ba&(~set_off_bit);
}

bit_array_t BitArraySetBit(bit_array_t ba, char set, size_t index)
{
    bit_array_t set_bit=~(1<<index);
    ba&=set_bit;
    set_bit=set<<index;
    
    return ba|set_bit;
}

bit_array_t BitArrayMirror(bit_array_t ba)
{
    ba = (((ba & 0xaaaaaaaaaaaaaaaa) >> 1) | ((ba & 0x5555555555555555) << 1));
    ba = (((ba & 0xcccccccccccccccc) >> 2) | ((ba & 0x3333333333333333) << 2));
    ba = (((ba & 0xf0f0f0f0f0f0f0f0) >> 4) | ((ba & 0x0f0f0f0f0f0f0f0f) << 4));
    ba = (((ba & 0xff00ff00ff00ff00) >> 8) | ((ba & 0x00ff00ff00ff00ff) << 8));
    ba = (((ba & 0xffff0000ffff0000) >> 16) | ((ba & 0x0000ffff0000ffff) << 16));
    ba = (((ba & 0xffffffff00000000) >> 32) | ((ba & 0x00000000ffffffff) << 32));
    
    return ba;
}

bit_array_t BitArrayMirrorLUT(bit_array_t ba)
{
    bit_array_t mirror_ba=ba;
    int i=0;

    for(i=0;i<16;++i)
    {
        mirror_ba<<=4;
        mirror_ba|=lut_mirror_nibble[ba&0xf];
        ba>>=4;
    }

    return mirror_ba;
}


bit_array_t BitArrayRotateRight(bit_array_t ba, size_t nbits)
{
    bit_array_t tmp_ba=ba;
    nbits%=(sizeof(bit_array_t)*CHAR_BIT);

    ba>>=nbits;
    tmp_ba<<=(sizeof(bit_array_t)*CHAR_BIT)-nbits;

    return ba|tmp_ba;
}

bit_array_t BitArrayRotateLeft(bit_array_t ba, size_t nbits)
{
    bit_array_t tmp_ba=ba;
    nbits%=(sizeof(bit_array_t)*CHAR_BIT);

    ba<<=nbits;
    tmp_ba>>=(sizeof(bit_array_t)*CHAR_BIT)-nbits;

    return ba|tmp_ba;
}

bit_array_t BitArrayFlip(bit_array_t ba)
{
    return ~ba;
}

bit_array_t BitArrayFlipBit(bit_array_t ba, size_t index)
{
    bit_array_t bit_to_flip=1;
    bit_to_flip<<=index;

    return ba^bit_to_flip;
}

size_t BitArrayCountOn(bit_array_t ba)
{
    ba = ((ba & 0x5555555555555555) + ((ba >> 1) & 0x5555555555555555));
    ba = ((ba & 0x3333333333333333) + ((ba >> 2) & 0x3333333333333333));
    ba = ((ba & 0x0f0f0f0f0f0f0f0f) + ((ba >> 4) & 0x0f0f0f0f0f0f0f0f));
    ba = ((ba & 0x00ff00ff00ff00ff) + ((ba >> 8) & 0x00ff00ff00ff00ff));
    ba = ((ba & 0x0000ffff0000ffff) + ((ba >> 16) & 0x0000ffff0000ffff));
    ba = ((ba & 0x00000000ffffffff) + ((ba >> 32) & 0x00000000ffffffff));
    
    return ba;
}

size_t BitArrayCountOnLUT(bit_array_t ba)
{
    int i=0;
    size_t count_on=0;
    for(i=0;i<16;++i)
    {
        count_on+=lut_bits_on_in_nibble[ba&0xf];
        ba>>=4;
    }

    return count_on;
}

size_t BitArrayCountOff(bit_array_t ba)
{
    size_t count_off=0;
    ba=~ba;

    while(ba)
    {
        ++count_off;
        ba=ba&(ba-1);
    }

    return count_off;
}

size_t BitArrayGetVal(bit_array_t ba, size_t index)
{
    return (ba>>index)&1;
}

char *BitArrayToString(bit_array_t ba, char *str)
{
    int num_of_bits=sizeof(bit_array_t)*CHAR_BIT;
    assert(str);
    while(num_of_bits)
    {
        *str=(ba &(size_t)0x8000000000000000?'1':'0');
        ++str;
        ba<<=1;
        --num_of_bits;
    }

    *str='\0';

    return str;
}

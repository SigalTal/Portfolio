/*********************************
 * Reviewer: Sivan  
 * Author: Sigal Tal		
 * File: bit_array.h
 * ******************************/
#include <stdio.h>/*printf - size_t*/
#include <string.h>/*strcmp*/
#include <assert.h>
#include "bit_array.h"

void TestSetAll(void);
void TestResetAll(void);
void TestSetOn(void);
void TestSetOff(void);
void TestSetBit(void);
void TestMirror(void);
void TestRotateRight(void);
void TestRotateLeft(void);
void TestFlip(void);
void TestFlipBit(void);
void TestCountOn(void);
void TestCountOff(void);
void TestGetVal(void);
void TestToString(void);
void TestCountOnLUT(void);
void TestMirrorLUT(void);

int main()
{
    TestSetAll();
    TestResetAll();
    TestSetOn();
    TestSetOff();
    TestSetBit();
    TestMirror();
    TestRotateRight();
    TestRotateLeft();
    TestFlip();
    TestFlipBit();
    TestCountOn();
    TestCountOff();
    TestGetVal();
    TestToString();
    TestCountOnLUT();
    TestMirrorLUT();
    

    return 0;
}

void TestSetAll(void)
{
    bit_array_t ba=6;
    ba=BitArraySetAll(ba);

    assert(ba==0xffffffffffffffff);
}

void TestResetAll(void)
{
    bit_array_t ba=6;
    ba=BitArrayResetAll(ba);

    assert(ba==0); 
}

void TestSetOn(void)
{
    bit_array_t ba=5;
    ba=BitArraySetOn(ba,1);
    assert(7==ba);
}

void TestSetOff(void)
{
    bit_array_t ba=5;
    ba=BitArraySetOff(ba,2);
    assert(1==ba);

}

void TestSetBit(void)
{
    bit_array_t ba=5;
    char set='1';
    size_t index=2;

    BitArraySetBit(ba, set, index);

    assert(5==ba);
}

void TestMirror(void)
{
    bit_array_t ba=1;
    ba=BitArrayMirror(ba);

    if(0x8000000000000000!=ba)
    {
        printf("Error Mirror\n");
    }
}

void TestMirrorLUT(void)
{
    bit_array_t ba=1;
    ba=BitArrayMirrorLUT(ba);

    if(0x8000000000000000!=ba)
    {
        printf("Error Mirror\n");
    }
}

void TestRotateRight(void)
{
    bit_array_t ba=8;
    size_t nbits=1;
    ba = BitArrayRotateRight(ba,nbits);

    assert(4==ba);
}

void TestRotateLeft(void)
{
    bit_array_t ba=5;
    size_t nbits=1;
    ba = BitArrayRotateLeft(ba,nbits);

    assert(10==ba);
}

void TestFlip(void)
{
    bit_array_t ba=0x0000000f00000f00;
    ba=BitArrayFlip(ba);

    if(0xfffffff0fffff0ff!=ba)
    {
        printf("Error Flip\n");
    }
}

void TestFlipBit(void)
{
    bit_array_t ba=5;
    ba=BitArrayFlipBit(ba,0);

    assert(ba==4);

}

void TestCountOn(void)
{
    size_t count=0;
    bit_array_t ba=5;
    count=BitArrayCountOn(ba);
    assert(2==count);
    (void)(count);
}

void TestCountOnLUT(void)
{
    size_t count=0;
    bit_array_t ba=5;
    count=BitArrayCountOnLUT(ba);
    assert(2==count);
    (void)(count);
}

void TestCountOff(void)
{
    size_t count=0;
    bit_array_t ba=5;
    count=BitArrayCountOff(ba);
    assert(62==count);
    (void)(count);

}

void TestGetVal(void)
{
    bit_array_t ba=5;
    size_t index=2;
    BitArrayGetVal(ba,index);

    assert(1==BitArrayGetVal(ba,index));
}

void TestToString(void)
{
    bit_array_t ba=3276;
    char str1[65]={0};
    char str2[65]="0000000000000000000000000000000000000000000000000000110011001100";
    BitArrayToString(ba, str1);

    assert(0==strcmp(str1,str2));
    (void)(str2);
}
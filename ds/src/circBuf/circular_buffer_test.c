/*********************************
 * Reviewer: 
 * Author: Sigal Tal
 * File Name: circular_buffer.h
 * ******************************/
#include <assert.h>
#include "circular_buffer.h"


void TestNewCBuff(void);
void TestBegSize(void);
void TestWriteCBuff(void);
void TestReadCBuff(void);

int main()
{
    TestNewCBuff();
    TestBegSize();
    TestWriteCBuff();
    TestReadCBuff();
    
    return 0;
}

void TestNewCBuff(void)
{
    size_t capacity=4;

    circ_buff_t *c_buff=CircBuffCreate(capacity);

    CircBuffDestroy(c_buff);
}

void TestBegSize(void)
{
    size_t capacity=4;

    circ_buff_t *c_buff=CircBuffCreate(capacity);

    assert(capacity==CircBuffBufSiz(c_buff));

    assert(capacity==CircBuffFreeSpace(c_buff));

    assert(1==CircBuffIsEmpty(c_buff));

    CircBuffDestroy(c_buff);
}

void TestWriteCBuff(void)
{
    size_t capacity=20, count=2, write=0;

    char *stream="sigal";

    circ_buff_t *c_buff=CircBuffCreate(capacity);

    write=CircBuffWrite(c_buff, stream, count);

    assert(2==write);

    assert(18==CircBuffFreeSpace(c_buff));

    CircBuffDestroy(c_buff);
}

void TestReadCBuff(void)
{
    size_t capacity=20, count=2, write=0, read=0;

    char *stream="sigal";

    char output[20]={0};

    circ_buff_t *c_buff=CircBuffCreate(capacity);

    write=CircBuffWrite(c_buff, stream, count);

    assert(2==write);

    assert(18==CircBuffFreeSpace(c_buff));

    read=CircBuffRead(c_buff, output, count);

    assert(2==read);

    assert(20==CircBuffFreeSpace(c_buff));

    CircBuffDestroy(c_buff);
}
/*********************************
 * Reviewer: 
 * Author: 
 * File Name: circular_buffer.h
 * ******************************/

#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <sys/types.h>	/* ssize_t size_t */

typedef struct circular_buffer circ_buff_t;

/*	Description: Creates a new circular buffer
	Parameters: Capacity - number of bytes
	Return Value: In case of success pointer to the new queue,
		      Null in case of failure
	Undefined Behavior:
	Complexity: O(1)*/ 
circ_buff_t *CircBuffCreate(size_t capacity);

/*	Description: Destroys the circular buffer 
	Parameters: Pointer to the circular buffer
	Undefined Behavior:
	Complexity: O(1)*/ 
void CircBuffDestroy(circ_buff_t *c_buff);

/*	Description: Checks the number of free bytes left to write 
	Parameters: Pointer to the circular buffer
	Return Value: Number of free bytes in the circular buffer
	Undefined Behavior: 
	Complexity: O(1)*/ 
size_t CircBuffFreeSpace(const circ_buff_t *c_buff);

/*	Description: Returns the buffer capacity
	Parameters: Pointer to the circular buffer
	Return Value: buffer capacity
	Undefined Behavior:
	Complexity: O(1)*/ 
size_t CircBuffBufSiz(const circ_buff_t *c_buff);

/*	Description: Checks if the buffer is empty 
	Parameters: Pointer to the circular buffer
	Return Value: Returns non-zero if Empty, 0 if not empty
	Undefined Behavior:
	Complexity: O(1)*/ 
int CircBuffIsEmpty(const circ_buff_t *c_buff);

/*	Description: Reads count number of bytes from the circular buffer
		     to the user's buffer
	Parameters: Pointer to the circular buffer,
		    Pointer to user's buffer,
		    count - number of bytes to read
	Return Value: Number of bytes read
	Undefined Behavior: if users stream is smaller the count, if stream is smaller then count
			    if count is bigger then capacity
	Complexity: O(n)*/ 
ssize_t CircBuffRead(circ_buff_t *c_buff, void *stream, size_t count);

/*	Description: Writes count number of bytes from the user's buffer
		     into the circular buffer
	Parameters: Pointer to the circular buffer,
   		    const Pointer to user's buffer,
   		    count - number of bytes to read
	Return Value: Number of bytes written
	Undefined Behavior: if count is bigger then users stream
			    if count is bigger then cb_t buffer
	Complexity: O(n)*/ 
ssize_t CircBuffWrite(circ_buff_t *c_buff, const void *stream, size_t count);

#endif /*__CIRCULAR_BUFFER_H__*/
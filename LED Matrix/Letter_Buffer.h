// Author: Matthew P. Burruss
// Date: 9/24/2018
// Brief: A modified version of the ex_buff.c class
// created during class. The circular buffer is used to
// contain Letter objects. Enqueue and Dequeue operations
// are protected by a conditional mutex


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Letter.h"

// max size of the queue
#define MAXSIZE  32

// actual queue
struct buffer {
	struct letter * myBuffer;
	int read,write,counter;
	pthread_mutex_t bufferMutex;
	pthread_cond_t bufferCondition;
};

// initializes the buffer
// All indices and counter are 0
void* buffer_init(struct buffer* b);

//enqueue
// Adds elements to the buffer
void* enqueue (struct buffer*b,char l);

// dequeue
// removes element from buffer
// name and value inputs now contain the removed element
struct letter dequeue (struct buffer*b);

// returns the size of the buffer
int size(struct buffer *b);

// frees the dynamic memory allocated to the buffer
void freeBuffer(struct buffer * mybuf);


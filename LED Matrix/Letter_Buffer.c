// Author: Matthew P. Burruss
// Date: 9/24/2018
// Brief: A modified version of the ex_buff.c class
// created during class. The circular buffer is used to
// contain Letter objects. Enqueue and Dequeue operations
// are protected by a conditional mutex

#include "Letter_Buffer.h"

void* buffer_init(struct buffer* b){
	b->myBuffer = malloc(MAXSIZE*sizeof(struct letter));
    b->read = 0;
	b->write = 0;
	b->counter = 0;
	pthread_cond_init(&(b->bufferCondition),NULL);
	pthread_mutex_init(&(b->bufferMutex),NULL);
	return NULL;
}

// enqueue
// Adds elements to the buffer
void* enqueue (struct buffer*b,char l){
	  pthread_mutex_lock( &(b->bufferMutex) ); // lock condition
      while(b->counter >= MAXSIZE)
      {
         pthread_cond_wait( &(b->bufferCondition) ,&(b->bufferMutex) );
      }
      // not full, let's add the value
      struct letter* newLetter = createLetter(l);
      b->myBuffer[b->write] = *newLetter;
      b->counter++;
      b->write = (b->write +1)%MAXSIZE;
      // send signal to wake
      pthread_cond_broadcast( &(b->bufferCondition) );
      // unlock mutex
      pthread_mutex_unlock( &(b->bufferMutex) );
      return NULL;
}

// dequeue
// removes element from buffer
// name and value inputs now contain the removed element
struct letter dequeue (struct buffer*b){
      pthread_mutex_lock( &(b->bufferMutex)); // lock condition
      while(b->counter == 0)
      {
        pthread_cond_wait( &(b->bufferCondition) ,&(b->bufferMutex) );
      }
      // not full, let's add the value
      struct letter removeMe = b->myBuffer[b->read];
      b->read = (b->read + 1)%MAXSIZE;
      b->counter--;
      // send signal to wake
      pthread_cond_broadcast( &(b->bufferCondition) );
      // unlock mutex
      pthread_mutex_unlock( &(b->bufferMutex) );
      return removeMe;
}

// returns the size of the buffer
int size(struct buffer *b)
{
    return b->counter;
}

// frees the dynamic memory allocated to the buffer
void freeBuffer(struct buffer * mybuf)
{
    free(mybuf->myBuffer);
}

/*
int main(void)
{
    struct buffer * mybuf = malloc(sizeof(struct buffer));
    buffer_init(mybuf);
    enqueue(mybuf,'A');
    enqueue(mybuf,'B');
    enqueue(mybuf,' ');
    printf("%d",size(mybuf));
    struct letter myletter;
    myletter = dequeue(mybuf);
    printLetter(&myletter);
    myletter = dequeue(mybuf);
    printLetter(&myletter);
    myletter = dequeue(mybuf);
    printLetter(&myletter);

}
*/


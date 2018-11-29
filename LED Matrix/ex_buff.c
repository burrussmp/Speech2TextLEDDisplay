// Author: Matthew P. Burruss
// Date: 9/24/2018
// Brief: A circular queue managed by conditional mutexes.
// There is 1 producer thread and 1 consumer thread
// that each add and remove 1000 elements respectively.
// initializes the buffer
// All indices and counter are 0
#include "ex_buff.h"

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

int size(struct buffer *b)
{
    return b->counter;
}

void freeBuffer(struct buffer * mybuf)
{
    free(mybuf->myBuffer);
}
/*
// Thread that adds 1000 elements
// Prints the element that has been added.
void *producer(struct buffer *b){
	// add 100 elements
	for (int i = 0; i < 1000; ++i){
		enqueue(b,'P',i);
		printf("Producer adding element: %d \n",i);
		fflush(stdout);
	}
    return NULL;
}


// Thread that removes elements
// Removes 1000 elements.
void *consumer(struct buffer *b){
	// add 100 elements
	//int *myInt = malloc(sizeof(int));
	//char*myChar = malloc(sizeof(char));
	//for (int i = 0; i < 1000; ++i){
	//	dequeue(b,myChar,myInt);
	//	printf("Consumer removing element %d (myChar = %c "
//				"and myInt = %d) \n",i,*myChar,*myInt);
//		fflush(stdout);
//	}
    return NULL;
}


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


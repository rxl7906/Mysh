#ifndef _QUEUEADT_H_
#define _QUEUEADT_H_

#include <stdbool.h>

typedef struct QueueNode{ 
	void *data;
	struct QueueNode *next;
	int seqNum; // sequence number
	pid_t pid; // process id
	// input command strings
	// pointer to a function
}QueueNode;
typedef struct QueueADT{ 
	struct QueueNode *initial;
}*QueueADT;

QueueADT que_create();

void printQueue( QueueADT queue );

bool que_empty( QueueADT queue );

void que_clear( QueueADT queue );

void que_destroy( QueueADT queue );

void que_insert( QueueADT queue, void *data, int listCounter );

void *que_remove( QueueADT queue );

#endif

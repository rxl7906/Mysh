#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "queueADT.h"

// create queue
QueueADT que_create() {
	// allocate memory block for queue
	QueueADT queue = malloc(sizeof(QueueADT));
	return queue;	
}

void printHelp(QueueNode *node) {
	if(!node->next){ // if there is no next node
		printf("%s,  ", node->data); // free the current node and return
		return;
	} else { // recursively free nodes until you hit base case
		printHelp(node);
	}
}

// print queue
void printQueue(QueueADT queue) {
	
	if ( que_empty( queue) ) { // check if queue is empty
		return; // return if queue is empty
	} else { // if queue is not empty
		printHelp(queue->initial); // free nodes in the queue
		
	}
}

// Indicate whether or not the supplied Queue is empty 
bool que_empty( QueueADT queue ) {
	if ( !queue->initial ) { // if there is no initial node
		return true; // return true that queue is empty
	} else { // if there is initial node
		return false; // return false
	}
}

/*
Helper Function
Free Node to remove all contents from each node recursively until 
the last node. 
*/
void freeNode(QueueNode * node) {
	if(!node->next){ // if there is no next node
		free(node); // free the current node and return
		return;
	} else { // recursively free nodes until you hit base case
		freeNode(node);
	}
}

// Remove all contents from the supplied QueueADT.
void que_clear( QueueADT queue) {
	if ( que_empty( queue) ) { // check if queue is empty
		return; // return if queue is empty
	} else { // if queue is not empty
		freeNode(queue->initial); // free nodes in the queue
		queue->initial=NULL; // set initial node to null
	}
}

// Tear down and deallocate the supplied QueueADT
void que_destroy( QueueADT queue) {
	que_clear( queue ); // remove all contents of the queue
	free( queue ); // deallocate the queue
}

/*
Helper Function
Recursively add nodes to the queue until there is no next node.
*/
void addNode( QueueNode* currentNode, QueueNode* newNode) {
	if(!currentNode->next){ // if there is no next node
		currentNode->next=newNode; // add the last node
		return;
	} else {
		addNode(currentNode->next,newNode); // recursively add nodes
	}
}

void que_insert( QueueADT queue, QueueNode *node ) {
	if(que_empty(queue)){ // if queue is empty
		queue->initial = node; // set initial node to new node with data
		return;
	}
	// add node
	addNode(queue->initial,node);
}

/*
Remove and return the first element from the QueueADT.

@param queue the QueueADT to be manipulated
@return the value that was removed from the queue
@exception If the queue is empty, the program should terminate
with an error message. This can be done by printing an 
appropriate message to the standard error output and then 
exiting with EXIT_FAILURE, or by having an assert() fail.
*/
void *que_remove( QueueADT queue) {
	QueueNode * removedNode; // create node
	void * returnData; // make void pointer

	if(que_empty( queue)) { // if the queue is empty, you can't remove
		exit(EXIT_FAILURE);
	}

	returnData = queue->initial->data; // hold initial's data
	removedNode = queue->initial; // hold initial node
	queue->initial = removedNode->next; // set initial node to node after initial
	free(removedNode); // deallocate memory space of removedNode
	return returnData; // return removedNode's data
}
/*
long int testData[] = { 42, 17, -12, 9982, 476, 2912, -22, 3291213, 7782 };
int numData = sizeof(testData) / sizeof(long int);

void process( QueueADT queue ) {
	long int i;

	fputs( "Inserting: ", stdout );
	for( i = 0; i < numData; ++i ) {
		printf( " %ld", testData[i] );
		que_insert( queue, (void *) testData[i] );
	}

	fputs( "\nRemoving:  ", stdout );
	while( !que_empty(queue) ) {
		i = (long int) que_remove( queue );
		printf( " %ld", i );
	}

	putchar( '\n' );
}*/

int main( void ) {
	QueueADT fifo;

	fifo = que_create(  );

	puts( "\nTesting the FIFO queue" );
	process( fifo );

	que_destroy( fifo );

	return( 0 );
}
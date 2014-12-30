#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "queueADT.h"

//
// Sequence of test values to be inserted and removed
//

long int testData[] = { 42, 17, -12, 9982, 476, 2912, -22, 3291213, 7782 };
int numData = sizeof(testData) / sizeof(long int);



//
// Process insertions/removals using a specific queue
//

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
}


int main( void ) {
	QueueADT fifo;

	fifo = que_create( );
	if( fifo == NULL ) {
		fputs( "Cannot create FIFO queue\n", stderr );
		exit( EXIT_FAILURE );
	}

	puts( "\nTesting the FIFO queue" );
	process( fifo );

	que_destroy( fifo );

	return( 0 );
}

// Revisions:
//	$Log: queueTest1.c,v $
//	Revision 1.2  2014/10/13 11:21:22  csci243
//	updated to 64 bit pointer architecture
//
//	Revision 1.1  2013/10/29 19:07:57  csci243
//	Initial revision
//

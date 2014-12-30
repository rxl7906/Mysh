/*
 * myshell.c - holds internal commands 
 * 
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "queueADT.h"

/*
 * Print list of internal commands.
 */
int _help_(int argc, char *argv[]){
	printf("%s\n","HELP");
	return 0;
}

int _history_(int argc, char *argv[]){
	printf("%s\n","HISTORY");
	return 0;
}

int _quit_(int argc, char *argv[]){
	printf("%s\n","QUIT");
	que_destroy(historyQueue);
	exit(EXIT_FAILURE);
	return 0;
}

int _verbose_on_(int argc, char *argv[]){
	printf("%s\n","VERBOSE ON");
	return 0;
}

int _verbose_off_(int argc, char *argv[]){
	printf("%s\n","VERBOSE OFF");
	return 0;
}

int _bang_(int argc, char *argv[]){
	printf("%s\n","BANG");
	return 0;
}


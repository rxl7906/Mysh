/*
 * mysh.c - simple interactive shell program that can execute UNIX commands
 * and some internal commands specified later. 
 * 1) Implement a program that gets each line of input from the terminal console
 * 2) Formulate the input into a user command
 * 3) Create a child process to execute that command
 * 4) Coninute to process each line entered until any of these events occur:
 * - User issues command to terminate shell
 * - User signals shell there is no more input
 * - Shell encounters the end of input (EOF)
 * - Shell encounters fatal error reading input
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "queueADT.h"
#include "mysh.h"


// declare static history queue
QueueADT historyQueue;

// static temp for bang command ( for quit command to have access )
char *temp; 

// default history number
extern int pos_num = 10;

// global boolean value for verbose (verbose on = 1) | (verbose off = 0)
int verbose = 0;

// bang number
int bangNumber;

// history list counter
int listCounter = 1;

// print list of internal commands
int help(int argc, char *argv[]){
	printf("1) !N: Re-execute the Nth command in the history list. Look up command in the list and rerun it to create the process another time. N must be valid within range of current history.\n");
	printf("2) help: Print a list of internal commands.\n");
	printf("3) history: Print a list of commands executed so far, including their arguments, depending on history list size\n");
	printf("4) quit: Clean up memory and gracefully terminate the shell\n");
	printf("5) verbose on/off: When verbose is on, shell should print a list of commands and their arguments, it should print the execution status value returned to the shell by the command.\n");
	return 0;
}
// print history
int history(int argc, char *argv[]){
	printQueue(historyQueue);	
	return 0;
}
// quit and deallocate memory
int quit(int argc, char *argv[]){
	printf("%s\n","QUIT");
	que_destroy(historyQueue);
	printf("%s\n","before free");
	free(temp);
	printf("%s\n","TESTING");
	exit(EXIT_FAILURE);
	return 0;
}

// turn verbose on
int verbose_on(int argc, char *argv[]){
	verbose = 1;
	return 0;
}

// turn verbose off
int verbose_off(int argc, char *argv[]){
	verbose = 0;
	return 0;
}
// bang command
int bang(int argc, char *argv[]){
	
	return 0;
}

// Parsing line and making string of tokens with null terminators
// Then add to the argv array. 
void parse(char *line, char **argv) {
	while( *line != '\0'){ // if not end of line
		while( *line == ' ' || *line == '\t' || *line =='\n') {
			*line++ = '\0'; // replace white spaces with 0
		}
		if (*line) {
			 *argv++ = line; // save argument position
		}
		while( *line != ' ' && *line != '\t' &&
			*line != '\n' && *line != '\0') {
			line++; // skip argument until....
		}
	}
	*argv = '\0'; // mark end of argument list
}

// Handles external commands
void execute(char **argv) {
	pid_t pid = fork();
	int status;
	if( pid < 0) {
		perror("fork failed\n");
	}
	else if( pid == 0 ) {	// child process
		if(verbose == 1) { // if verbose is on
			printf("\twait for pid %d: %s\n", getpid(), argv[0] );
			printf("\texecvp: %s\n",argv[0]);
		}
		if (execvp(*argv,argv) < 0) {
			printf("Exec failed\n");
			exit(1);
		}
	}
	else { // getting here means we are parent
		wait(&status);
	}
}

extern char *optarg;

int main(int argc, char *argv[]) {
	
	int args; // holds verbose and history arguments

	// check for verbose and history number
	while( (args = getopt(argc, argv, "vh:")) != -1 ) {
		switch(args) {
			case 'v': // verbose on/off
				verbose_on(argc,argv);
				break;
			case 'h': // take in history list size
				pos_num = atoi(optarg);
				if(pos_num < 1) {
					fprintf(stderr,"usage: %s [-v] [-h pos_num]\n", argv[0]);
					exit(EXIT_FAILURE);
				}
				break;
			default:
				fprintf(stderr,"usage: %s [-v] [-h pos_num]\n",argv[0]);
		}
	}
	// create queue with history list size
	historyQueue = que_create();

	size_t len = 0;
	char *command; // for getline's first parameter
	char *token; // first token
	char *inputline = malloc(sizeof(char*)); // for external commands
	char *array[100000]; // for external commands
	char *line; // put inputline's contents in line
	char *verboseTable[100000]; // parsing verbose

	printf("mysh[%d]> ",listCounter);
	// run loop waiting for user commands
	while( getline(&command, &len, stdin ) != -1 )  {
		// get line of text with commands and their arguments
		strcpy(inputline,command); // for inputline

		// parse command into tokens
		token = strtok(command, " "); // get first token

		temp = malloc(1); // account for bang
		strncpy(temp, token, 1); // account for bang 
		char *bangCMD = malloc(sizeof(char*)); // allocate memory for bang

		// get rid of new line (this is for external commands)
		line = strtok(inputline, "\n");

		char *verboseLine = malloc(sizeof(char*)); // for verbose
		strcpy(verboseLine,line); // put line contents into verbose
		parse(verboseLine, verboseTable); // parse verboseline

		if( verbose == 1 ) { // if verbose is on
			printf("\tcommand: ");
			int count = 0;
			while(verboseTable[count] != NULL){
				printf("%s ",verboseTable[count]);
				count+=1;
			}
			printf("\n\n");
			printf("\tinput command tokens:\n");
			int count2 = 0;
			while(verboseTable[count2] != NULL) {
				printf("\t%d: %s\n",count2,verboseTable[count2]);
				count2+=1;
			}
		}
		if( strcmp("\n", token) == 0 ){	// take care of white spaces
			printf("here?");
		}
		else if( strcmp("help\n", token) == 0){ // help
			que_insert(historyQueue, "help", listCounter); // insert
			help(argc,argv); // run help function
			listCounter+=1;
		} 
		else if( strcmp("history\n",token) == 0){ // history
			que_insert(historyQueue, "history", listCounter); // insert
			history(argc,argv); // run history function
			listCounter+=1;
		} 
		else if( strcmp("quit\n",token) == 0){ // quit
			que_insert(historyQueue, "quit", listCounter);
			quit(argc,argv); // run quit function
			listCounter+=1;
		} 
		else if( strcmp("verbose on",line) == 0) { // verbose on
			que_insert(historyQueue,"verbose on",listCounter);
			verbose_on(argc,argv); // run verbose on function
			listCounter+=1;
		} 
		else if( strcmp("verbose off", line) == 0) { // verbose off
			que_insert(historyQueue,"verbose off",listCounter);
			verbose_off(argc,argv); // run verbose off function
			listCounter+=1;
		}
		else if( strcmp("verbose\n", token) == 0 ) { // other than on/off
			que_insert(historyQueue,token,listCounter);
			listCounter+=1;
		}
		else if( strcmp("!",temp) == 0 ){ // bang
			strcpy(bangCMD,line); // copy line into bangCMD
			char *bangNum; 
			bangNum = strtok(token,"!"); // get bang number
			bangNumber = atoi(bangNum);
			bang(argc,argv); // run bang function
			que_insert(historyQueue,bangCMD, listCounter);
			listCounter+=1;
		}
		else{ // for external commands
			// temporary external variable for storing in history list
			char *externalCMD = malloc(sizeof(char*));
			strcpy(externalCMD,line);
			que_insert(historyQueue, externalCMD, listCounter);
			line[strlen(line)] = '\0'; // add null terminator
			parse(line, array); // parse the array for external cmd
			execute(array); // handle external command
			listCounter+=1;
		}
		printf("mysh[%d]> ",listCounter);

	}
}

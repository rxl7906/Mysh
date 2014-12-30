Project2: mysh: My Shell
Author: Robin Li
------------------------------------------------------------------------
FILES SUBMITTED:
- mysh.c
- mysh.h
- queueADT.c
- queueADT.h
- README.txt
------------------------------------------------------------------------
DESIGN:
- The project can be described as low cohesion because the program does a 
great variety of actions. 
- The approach taken for this project was a top-down design to make sure 
I could promt and loop, then do input retrieval,
then parse, and so forth. 
- getopt() was used to process command line options
- getline() was used to take in commands
- Run strcmp() for handling internal commands then handle the external 
commands in the else case along with a fork point to create a child process
to execute that command. 
- The queueADT.c/queueADT.h handles the queue data structure used to 
implement the history list. 
------------------------------------------------------------------------
DATA STRUCTURES:
- I implemented a queueADT to handle the history list along with creating
specific queue nodes. 
------------------------------------------------------------------------
DESIGN FLAWS:
- The main function in the mysh.c contains too code and by doing so makes
things less moduler. This project should have implemented a separate function
that handled the internal commands and another function to handle the 
external commands for the getline() function in another .c file.
- The mysh.c has too much content and should be separated into smaller
.c file to create high cohesion and low coupling. 
- The internal functions are all in the mysh.c which is not ideal. 
- I should have made good use of the mysh.h by creating high cohesion and 
low coupling, and to decrease the code in mysh.c
- For the internal commands, I did not make use of the (int argc, char *argv[])
which I should have, not only due to requirements but to provide bang
with access to what the bang number is. 
------------------------------------------------------------------------
ATTENTION GRADER: 
- The queueADT.c and queueADT.h files there to give the separation
function a queue to use. 
Sementation Faults:
- WHEN YOU PRESS ENTER.
Errors:
- Entering verbose and then something that is not on/off results in 
"EXEC FAILED" being printed out.
- When you go from verbose on to verbose off, when verbose off command
is run, is still uses the diagnostic mode but after it turns it off. 
Memory Issues:
- Due to 4 instances of using malloc along with when inserting a node,
a queuenode is malloced memory, there are memory leaks that are difficult
to diagnose.
- When using the "quit" function, it tries to deallocate the memory,
however a segmentation fault occurs. 
------------------------------------------------------------------------
WHAT WORKS:
1) It can read all the internal commands, handle white spaces.
2) It can handle external commands.
3) Functions: help, history, verbose on, verbose off work. 
4) All the external commands work.
WHAT DOESN'T WORK:
1) Functions: quit, bang
------------------------------------------------------------------------
WARNINGS:
- The first warning:
"warning: 'pos_num' initialized and declared 'extern' [enabled by default]"
Explanation: The extern variable should have been declared in the header file.

- The internal command warnings:
Explanation: All the internal command don't use the (int argc or char*argv[])

- The last warning:
In function 'printHelp':
queueADT.c:23:2: warning: format '%s' expects argument of type 'char *', but argument 3 has type 'void *' [-Wformat=]
  printf("%d: %s\n", node->seqNum, node->data);
  ^
Explanation: The printHelp function is queueADT.c uses a print statement
that expects 'node->data' to be a 'char *' but the 'node->data' is a 'void *'
------------------------------------------------------------------------

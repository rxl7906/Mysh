#Mysh

Mysh is an interactive shell capable of executing simple UNIX 
commands and some implemented internal commands. 

## Background

Goal is to understand how to spawn subprocesses, how to implement
internal commands, and handle errors. Builds upon skills of 
dynamic memory management, text I/O, string manipulation, and
the design and use of structures. 

## Installation

1. Download MinGW to obtain the GNU Compiler Collection(GNU) for compiling C programs. 
2. Download zip file.

## Usage

1. Use header.mak to generate the make file and use the make file to create the executable.
(If executable "mysh" is there, skip this step)
2. Type "./mysh" to run shell.
3. Type in any external UNIX commands or the internal commands below.

###Internal Commands

1. help - print a list of internal commands
2. history - print a list of commands executed so far
3. verbose on/off - When verbose is on, shell prints a list of commands and
their arguments

## History

Project 3 of CSCI243 - Mechanics of Programming 

## Credits

Author: Robin Li

## License

The MIT License (MIT)

Copyright (c) 2014 Robin Li

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

#
# Created by gmakemake (Ubuntu Jul 25 2014) on Thu Dec 11 02:32:06 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CC =		gcc
CFLAGS =	-Wall -Wextra -pedantic -ggdb -std=c99

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	mysh.c queueADT.c
PS_FILES =	
S_FILES =	
H_FILES =	mysh.h queueADT.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	queueADT.o 

#
# Main targets
#

all:	mysh 

mysh:	mysh.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mysh mysh.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

mysh.o:	mysh.h queueADT.h
queueADT.o:	queueADT.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) mysh.o core

realclean:        clean
	-/bin/rm -f mysh 

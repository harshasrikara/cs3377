#!/usr/bin/make -f
#
# Filename:		Makefile
# Date:			04/05/2020
# Author:		Harsha Srikara
# Email:		harshasrikara@utdallas.edu
# Version:		1.0
# Copyright:		2020, All Rights Reserved
#
# Description: Makefile for asssignment 4
#
# Flags for the C++ implicit rules
CC = gcc
CCFLAGS = -Wall
CPPFLAGS = 

# Flags for the Lex implicit rules
#
# Implicit Makefile rule to use Lex for C programs
#
#   n.c is made automatically from n.l by running Lex. The actual recipe is
#	$(LEX) $(LFLAGS)
LEX = /bin/flex
LFLAGS = 


# Additional Flags for bison
YACC = /bin/bison
YFLAGS = -dy

#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters
PROJECTNAME = Assignment4

EXECFILE = a.out

OBJS = parse.o scan.o myproject.o

# Because we are insane, keep the intermediate files so we can look at
# them If we comment this out (or remove it), the intermediate scan.c
# file is automatically deleted.
.PRECIOUS: scan.c

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#* scanner scan.c

$(EXECFILE):	$(OBJS)
	$(CC) -o $@ $(OBJS)
	ln -fs ./$@ scanner
	ln -fs ./$@ parser

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

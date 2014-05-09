#############################################################################
#
#  makefile for tree traversal
#
#############################################################################
#
#  If you move this makefile, update the variable below
#  or else depend won't work.
#
#############################################################################

MAKEFILE	= Makefile
CC		= g++
CFILES		= main.cpp LQueue.cpp AQueue.cpp Array.cpp Queue.cpp getopt.cpp Tree_Factory_Impl.cpp Traversal_Strategy_Impl.cpp Options.cpp Tree_Factory.cpp Traversal_Strategy.cpp Tree_Iterator.cpp Tree_Iterator_Impl.cpp Print_Visitor.cpp Eval_Visitor.cpp Interpreter.cpp
HFILES		= LQueue.h AQueue.h Array.h Queue.h getopt.h Tree_Factory_Impl.h Traversal_Strategy_Impl.h Options.h Typedefs.h Tree_Factory.h Traversal_Strategy.h Tree.h Node.h Tree_Iterator.h Tree_Iterator_Impl.h Visitor.h Print_Visitor.h Eval_Visitor.h Interpreter.h
OFILES		= main.o LQueue.o AQueue.o Array.o getopt.o Queue.o Tree_Factory_Impl.o Traversal_Strategy_Impl.o Options.o Tree_Factory.o Traversal_Strategy.o Tree_Iterator.o Tree_Iterator_Impl.o Print_Visitor.o Eval_Visitor.o Interpreter.o

#############################################################################
# Flags for Installation
#############################################################################
BINDIR		= .
#############################################################################

DFLAGS		= -ggdb
IFLAGS          = 
OPTFLAGS	=  # Enable this flag if compiler supports templates...
LDFLAGS		= -g
CFLAGS		= $(IFLAGS) $(OPTFLAGS) $(DFLAGS)

#############################################################################
# G++ directives
#############################################################################
.SUFFIXES: .C .cpp
.cpp.o:
	$(CC) $(CFLAGS) -c $<
#############################################################################

all: tree-traversal

tree-traversal: $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $@

clean:
	/bin/rm -f *.o *.out *~ core

realclean: clean
	/bin/rm -rf tree-traversal

depend:
	g++dep -f $(MAKEFILE) $(CFILES) 

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

main.o: main.cpp Tree.h Node.h Node.cpp Typedefs.h Tree.cpp \
  Tree_Factory.h Traversal_Strategy.h Options.h Tree_Iterator.h Print_Visitor.h Eval_Visitor.h Interpreter.h
getopt.o: getopt.cpp
Options.o: Options.cpp Options.h getopt.h
LQueue.o: LQueue.h LQueue.cpp
AQueue.o : AQueue.cpp AQueue.h
Queue.o  : Queue.cpp Queue.h
Array.o: Array.cpp Array.h Array.inl
Tree_Factory_Impl.o: Tree_Factory_Impl.h Tree_Factory_Impl.cpp
Traversal_Strategy_Impl.o: Traversal_Strategy_Impl.h Traversal_Strategy_Impl.cpp
Tree_Factory.o: Tree_Factory.h Tree_Factory.cpp
Traversal_Strategy.o: Traversal_Strategy.h Traversal_Strategy.cpp
Tree_Iterator.o: Tree_Iterator.h Tree_Iterator.cpp
Tree_Iterator_Impl.o: Tree_Iterator_Impl.h Tree_Iterator_Impl.cpp
Print_Visitor.o: Print_Visitor.h Print_Visitor.cpp
Eval_Visitor.o: Eval_Visitor.h Eval_Visitor.cpp
Interpreter.o: Interpreter.h Interpreter.cpp

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY

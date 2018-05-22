CXXFLAGS = -g -Wall -Werror -ansi -pedantic
CXX = g++ -std=c++11
CC = g++ -std=c++11

all: lexer
lexer.o: lexer.h lexer.cc 
paser.o :lexer.h paser.h paser2.cc
paser: paser.o lexer.o
lexer: lexer.o

clean: 
	rm -f *~ *.o

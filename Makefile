# A simple makefile for cse100 P2
#
# use g++ for everything
CC= g++

#include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -std=c++11 -g -Wall

#include debugging symbols in executable
LDFLAGS= -g

rst: test_RST.o
		g++ -o rst test_RST.o countint.o 

benchtree: benchtree.o
		g++ -o benchtree benchtree.o countint.o 

bst: test_BST.o
		g++ -o bst test_BST.o

test_RST.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp countint.o  

test_BST.o: BST.hpp BSTNode.hpp BSTIterator.hpp

benchtree.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp countint.o  

countint.o: countint.hpp
clean:
		rm bst rst benchtree *.o


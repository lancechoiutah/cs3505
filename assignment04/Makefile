# Name: Lance Choi
# Date: Feb 5, 2026
# Description: Makefile for assignment4. Builds the trieTest executable.

CXX = g++
CXXFLAGS = -Wall -std=c++11 -g -fsanitize=address

# Target: trieTest
trieTest: trie.o trieTest.o
	$(CXX) $(CXXFLAGS) -o trieTest trie.o trieTest.o

# Target: trie.o
trie.o: trie.cpp trie.h
	$(CXX) $(CXXFLAGS) -c trie.cpp

# Target: trieTest.o
trieTest.o: trieTest.cpp trie.h
	$(CXX) $(CXXFLAGS) -c trieTest.cpp

# Target: clean
clean:
	rm -f *.o trieTest

# Target: test
# Assumes you have words.txt and queries.txt in the same directory
test: trieTest
	./trieTest words.txt queries.txt
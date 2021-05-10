# Makefile for Assignment 2
# HOW TO USE
# 1. Download ex1, ex2 and ex3 from the assignment spec page, unzip
#    them and move them to your assignment directory
#
# 2. Your directory structure should look like:
#    ass2/
#        ex1/
#            collection.txt
#            invertedIndex.txt
#            ...
#        ex2/
#            collection.txt
#            invertedIndex.txt
#            ...
#        ex3/
#            collection.txt
#            invertedIndex.txt
#            ...
#        Makefile (this Makefile)
#        pagerank.c
#        searchPagerank.c
#        Your other files...
#
# 3. Read the notes below and edit the Makefile accordingly
#
# 4. After you use the make command, this will create executables in
#    the ex1, ex2 and ex3 directories. Change into these directories
#    and run your programs (e.g., ./pagerank)

CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

# Notes:
# Your pagerank.c should have the main() function for Part 1
# Your searchPagerank.c should have the main() function for Part 2
# Your scaledFootrule.c should have the main() function for Part 3
# List all your C files that DON'T contain a main() function here
# For example: SRC_FILES = hello.c world.c
SRC_FILES = readData.c Graph.c DLList.c Queue.c

.PHONY: all
# Uncomment each of these as you start working on them
all: pagerank searchPagerank scaledFootrule

pagerank: pagerank.c $(SRC_FILES)
	$(CC) $(CFLAGS) -o ex1/pagerank pagerank.c $(SRC_FILES)
	cp ex1/pagerank ex2/pagerank
	cp ex1/pagerank ex3/pagerank

searchPagerank: searchPagerank.c $(SRC_FILES)
	$(CC) $(CFLAGS) -o ex1/searchPagerank searchPagerank.c $(SRC_FILES)
	cp ex1/searchPagerank ex2/searchPagerank
	cp ex1/searchPagerank ex3/searchPagerank

scaledFootrule: scaledFootrule.c $(SRC_FILES)
	$(CC) $(CFLAGS) -o ex1/scaledFootrule scaledFootrule.c $(SRC_FILES)
	cp ex1/scaledFootrule ex2/scaledFootrule
	cp ex1/scaledFootrule ex3/scaledFootrule

.PHONY: clean
clean:
	rm -f ex?/pagerank ex?/searchPagerank ex?/scaledFootrule
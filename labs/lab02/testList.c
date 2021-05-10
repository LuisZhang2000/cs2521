// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

void testInsBefore(DLList L);
void testInsAfter(DLList L);
void testDelete(DLList L);

int main (void)
{
	printf("\n\n\n----TESTING FOR INSERT BEFORE, INSERT AFTER AND DELETE FUNCTIONS----\n\n\n");
	printf("Enter a character: ");
	DLList myList = getDLList (stdin);
	//putDLList (stdout, myList);
	assert (validDLList (myList));
	
	testInsBefore(myList);
	testInsAfter(myList);
	testDelete(myList);
	
	freeDLList (myList);
	return EXIT_SUCCESS;
}

void testInsBefore(DLList L) 
{
	printf("--------------TESTING INSERT BEFORE--------------\n");
	printf("This test inserts integers from 1 to 3 before the current node\n");
	//printf("Expected output: 3 2 1 %s\n", DLListCurrent(L));
	printf("Current Value: %s\n", DLListCurrent(L));
	printf("Current List: \n");
	putDLList(stdout, L);
	for (int i = 3; i >= 1; i--) {
		char string[20];
		sprintf(string, "%d", i);
		DLListBefore(L, string);
	}
	printf("NEW LIST: \n");
	putDLList(stdout, L);
	
	assert(validDLList(L));
	printf("--------------END OF TEST--------------\n\n\n");
}


void testInsAfter(DLList L)
{
	printf("--------------TESTING INSERT AFTER--------------\n");
	printf("This test inserts integers from 4 to 6 after the current node\n");
	//printf("Expected output: 5 4 3 2 1 %s\n", DLListCurrent(L));
	printf("Current Value: %s\n", DLListCurrent(L));
	printf("Current List: \n");
	putDLList(stdout, L);
	for (int i = 6; i >= 4; i--) {
		char string[20];
		sprintf(string, "%d", i);
		DLListAfter(L, string);
	}
	printf("NEW LIST: \n");
	putDLList(stdout, L);
	
	assert(validDLList(L));
	printf("--------------END OF TEST--------------\n\n\n");
}


void testDelete(DLList L)
{
	printf("--------------TESTING DELETE--------------\n");
	
	printf("Current Value: %s\n", DLListCurrent(L));
	printf("Current List: \n");
	putDLList(stdout, L);
	
	DLListMoveTo(L, 1);
	printf("Moving Current to 1st Position...\n");
	printf("Current Value: %s\n", DLListCurrent(L));
	
	printf("Deleting First Node: %s\n", DLListCurrent(L));
	DLListDelete(L);
	
	printf("Current List: \n");
	putDLList(stdout, L);
	
	printf("List Length: %zu\n", DLListLength(L));
	//int len = DLListLength(L);
	//DLListMoveTo(L, DLListLength(L));
	//printf("Deleting Last Node: %s\n", DLListCurrent(L));
	
	printf("Deleting 3 More Nodes: \n");
	DLListDelete(L);
	DLListDelete(L);
	DLListDelete(L);
	
	printf("Current List: \n");
	putDLList(stdout, L);
	
	printf("Deleting 2 More Nodes: \n");
	DLListDelete(L);
	DLListDelete(L);
	
	printf("Current List: \n");
	putDLList(stdout, L);
	
	printf("Deleting The Last Node: \n");
	DLListDelete(L);
	
	printf("Current List: \n");
	putDLList(stdout, L);
	
	printf("Attempting to Delete in an Empty List: \n");
	DLListDelete(L);
	
	printf("Current List: \n");
	putDLList(stdout, L);
	
	assert(validDLList(L));
	printf("--------------END OF TEST--------------\n\n\n");
}


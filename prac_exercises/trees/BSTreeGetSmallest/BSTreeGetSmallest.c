
#include "BSTree.h"

#include <stdlib.h>
/*
BSTree BSTreeGetSmallest(BSTree t) {
	
	if (t == NULL) {
		return NULL;
	}
	BSTree curr = t;
	while(curr->left != NULL) {
		curr = curr->left;
	}
	return curr;

}
*/
BSTree BSTreeGetSmallest(BSTree t) {
	
	// base case #1
	if (t == NULL) {
		return NULL;
	}

	// base case #2
	if (t->left == NULL) {
		return t;
	}
	
	// recursive case
	return BSTreeGetSmallest(t->left);

}
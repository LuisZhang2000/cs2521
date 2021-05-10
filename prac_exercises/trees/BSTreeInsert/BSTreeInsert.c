
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree newBSTreeNode(int val) {

	BSTree t = malloc(sizeof(struct BSTNode));
	t->value = val;
	t->left = NULL;
	t->right = NULL;
	return t;
}

BSTree BSTreeInsert(BSTree t, int val) {
	
	if (t == NULL) {
		t = newBSTreeNode(val);
		return t;
	}
	else if (val < t->value) {
		t->left = BSTreeInsert(t->left, val);
		return t;
	} else if (val > t->value) {
		t->right = BSTreeInsert(t->right, val);
		return t;
	} else {
		return t;
	}
}


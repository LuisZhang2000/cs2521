
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree join(BSTree t1, BSTree t2) {
	if (t1 == NULL) return t2;
	else if (t2 == NULL) return t1;
	else {
		BSTree curr = t2;
		BSTree parent = NULL;
		while (curr->left != NULL) {
			parent = curr;
			curr = curr->left;
		} 
		if (parent != NULL) {
			parent->left = curr->right;
			curr->right = t2;
		}
		curr->left = t1;
		return curr;
	}
}

BSTree BSTreeTrim(BSTree t, int lower, int upper) {
	
	BSTree new;

	if (t != NULL ) {	// nothing to do if tree is empty
		if (lower < t->value && upper < t->value) {	// delete items in left subtree
			t->left = BSTreeTrim(t->left, lower, upper);
		}
		else if (lower > t->value && upper > t->value) {	// delete items in right subtree
			t->right = BSTreeTrim(t->right, lower, upper);
		} 
		else {	// node 't' must be deleted
			if (t->left == NULL && t->right == NULL) {
				new = NULL;	// 0 children
			}
			else if (t->left == NULL) {
				new = t->right;	// 1 child
			}
			else if (t->right == NULL) {
				new = t->left;	// 1 child
			}
			else {
				new = join(t->left, t->right);	// 2 children
			}
			free(t);
			t = new;
			return BSTreeTrim(t, lower, upper);
		}
	}
	return t;
}


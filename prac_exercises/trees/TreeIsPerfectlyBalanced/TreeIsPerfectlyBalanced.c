
#include <stdlib.h>

#include "tree.h"

int BSTreeNumNodes(Tree t) {

	if (t == NULL)
		return 0;

	int lh = BSTreeNumNodes(t->left);
	int rh = BSTreeNumNodes(t->right);
	return 1 + lh + rh;
}

bool TreeIsPerfectlyBalanced(Tree t) {
	
	if (t == NULL) 
		return true;

	int lh = BSTreeNumNodes(t->left);
	int rh = BSTreeNumNodes(t->right);

	if (abs(lh - rh) <= 1 && TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right)) 
		return true;

	return false;
}


#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int height(Tree t);

bool TreeIsPerfectlyBalanced(Tree t) {
	
	if (t == NULL) {
		return true;
	}

	int leftH = height(t->left);
	//printf("left: %d\n", leftH);
	int rightH = height(t->right);
	//printf("right: %d\n", rightH);

	if (abs(leftH - rightH) <= 1 && TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right)) {
		return true;
	}

	if ((t->left == NULL && t->right != NULL) || (t->left != NULL && t->right == NULL)) {
		return false;
	}

	return false;
}

int height(Tree t) {
	if (t == NULL) {
		return -1;
	}
	int lh = height(t->left);
	int rh = height(t->right);
	return 1 + (lh > rh ? lh : rh);
}
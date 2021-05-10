#include <stdlib.h>

#include "tree.h"

// count #nodes in BSTree
int BSTreeNumNodes (Tree t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + BSTreeNumNodes (t->left) + BSTreeNumNodes (t->right);
}

bool TreeIsPerfectlyBalanced(Tree t) {
	if (t == NULL) {
        return true;
    }

    int lh = BSTreeNumNodes(t->left);
    int rh = BSTreeNumNodes(t->right);

    if (abs(lh - rh) <= 1 && TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right)) {
        return true;
    } 

    return false;
}
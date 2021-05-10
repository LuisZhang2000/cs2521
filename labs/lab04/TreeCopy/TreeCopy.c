
#include "tree.h"

Tree TreeCopy(Tree t, int depth) {
	
	if (t == NULL || depth < 0) {
		return NULL; 
	}

	Tree newTree = (Tree) malloc(sizeof(struct node));
	newTree->value = t->value;
	newTree->left = TreeCopy(t->left, depth - 1);
	newTree->right = TreeCopy(t->right, depth - 1);

	return newTree;

}


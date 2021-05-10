#include <stdlib.h>

#include "BSTree.h"

int BSTreeGetKthFurther(BSTree t, int k);

// global variable
int count = 0;
int kth = -1;

int BSTreeGetKth(BSTree t, int k) {
	kth = -1; 
	count = 0; 

	return BSTreeGetKthFurther(t, k);
}

int BSTreeGetKthFurther(BSTree t, int k) {
	if (t == NULL) {
		return kth;
	}

	BSTreeGetKthFurther(t->left, k);
	if (count == k) {
		kth = t->value; 
	} 
	count++;
	BSTreeGetKthFurther(t->right, k);

	return kth;
}
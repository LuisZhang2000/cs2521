// equalBST.c ... implementation of equalBST function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int equalBST(BSTree t1, BSTree t2) {
	
    if (t1 == NULL && t2 == NULL) {
        return 1;
    } else if (t1 == NULL || t2 == NULL) {
        return 0;
    } else if (key(t1) != key(t2)) {
        return 0;
    } else {
        return equalBST(left(t1), left(t2)) && equalBST(right(t1), right(t2));
    }
}


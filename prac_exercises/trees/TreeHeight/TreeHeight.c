
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    
    if (t == NULL) {
        return -1;
    }
    int lh = TreeHeight(t->left);
    int rh = TreeHeight(t->right);

    if (lh > rh) {
        return 1 + lh;
    } else {
        return 1 + rh;
    }
}


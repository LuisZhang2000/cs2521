int BSTreeMaxBranchLen(BSTree t) { 
    
    if (t == NULL) {
        return -1;
    }
    else if (t->left == NULL && t->right == NULL) {
        return 0;
    }
    

}
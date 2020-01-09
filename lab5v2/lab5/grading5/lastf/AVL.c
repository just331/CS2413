#include "stdheader.h"
#include "AVL.h"
AVLnode* createNode(Element e){
    AVLnode* node = (AVLnode*)malloc(sizeof(AVLnode));
    node -> left = NULL;
    node -> right = NULL;
    node -> e = e;
    return node;
}



int compare(int left, int right){
    
    if(left < right){
        return -1;
    }
    else if(left > right){
        return 1;
        
    }
    else{
        return 0;
    }
    
}



int count(AVLnode* n, int V){
    if(n == NULL){
        return 0;
    }
    else{
        int nV = n -> e.H * n -> e.D * n -> e.W;
        if(nV == V){
            return 1 + count(n -> left, V) + count(n -> right, V);
        }
        else{
            return count(n -> left, V) + count(n -> right, V);
        }
    }
}

int treeHeight(AVLnode*n){
    if (n == NULL){
        return 0;
    }
    return n -> height;
}

int max(int a,int b){
    return (a > b)? a : b;
}

AVLnode * RecalcHeight(AVLnode* n){
    if( n != NULL){
        n -> height = max(treeHeight(n -> left), treeHeight(n -> right)) + 1;
    }
    return n;
}

bool Balanced(AVLnode * n){
    if( n == NULL){
        return true;
    }
    int diff = treeHeight(n -> left) - treeHeight(n -> right);
    // diff >= -1 || diff <= 1
    if(-1 <= diff <= 1){
        return true;
    }
    return false;
}

AVLnode* RotateRight(AVLnode * n){
    if(n == NULL){
        return n;
    }
    if(n -> left == NULL){
        return n;
    }
    AVLnode* newroot = n -> left;
    n -> left = newroot -> right;
    newroot -> right = n;
    RecalcHeight(n);
    RecalcHeight(newroot);
    return newroot;
}

AVLnode* Rotateleft(AVLnode * n){
    if(n == NULL){
        return n;
    }
    if(n -> right == NULL){
        return n;
    }
    AVLnode* newroot = n -> right;
    n -> right = newroot -> left;
    newroot -> left = n;
    RecalcHeight(n);
    RecalcHeight(newroot);
    return newroot;
}

AVLnode* Rebalance(AVLnode* n){
    if(n == NULL){
        return n;
    }
    if(treeHeight(n -> left) > treeHeight(n -> right) + 1){
        if( treeHeight(n -> left -> right) > treeHeight(n -> left -> left))
            n -> left = Rotateleft(n -> left);
        return RotateRight(n);
    }
    else if(treeHeight(n -> right) > treeHeight(n -> left)+ 1){
        if(treeHeight(n -> right -> left) > treeHeight(n -> right -> right)){
            n -> right = RotateRight(n -> right);
        }
        return Rotateleft(n);
    }
    RecalcHeight(n);
    return n;    
}
    



AVLnode* add(AVLnode* n, Element e){
    if(n == NULL){
       n = createNode(e);
       return n;
    }
    else{
        int cmp = compare(n -> e.V, e.V);
        if( cmp == -1){
            n->right = add(n -> right, e);
            Rebalance(n);
        }
        else{
            n->left = add(n -> left, e);
            Rebalance(n);
        }
    }
}

AVLnode * removeHelp(AVLnode*n, AVLnode* replace, bool *deleted){
    if(n == NULL){
        return n;
    }
    if(n -> right != NULL){
        n -> right = removeHelp(n -> right, replace, deleted);
        return Rebalance(n);
        
    }
    else{
        replace -> e = n -> e;
        AVLnode* left = n -> left;
        free(n);
        *(deleted) = true;
        return left;
    }
}


AVLnode * removeNode(AVLnode* n, int e, bool *deleted){
    if(n == NULL){
        return n;
    }
    int cmp = compare(n -> e.V, e);
    if(cmp == -1){
        n -> left = removeNode(n -> left, e, deleted);
    }
    else if(cmp == 1){
        n -> right = removeNode(n -> right, e, deleted);
    }
    else{
        *deleted = true;
        if(n -> left == NULL){
            AVLnode* newroot = n -> right;
            free(n);
            return newroot;
        }
        else{
            n -> left = removeHelp(n -> left, n, deleted);
        }
    }
    return Rebalance(n);
}

void removeAll(AVL* t, int V){
    bool del = true;
    while(del == true){
        del = false;
        t->root->left = removeNode(t -> root -> left, V, &del);
    }
    
    del = true;
    while(del == true){
        del = false;
        t->root->right = removeNode(t-> root -> right, V, &del);
    }
    t->root = removeNode(t -> root, V, &del);
    return;
}


void inorderRec(AVLnode *n){
    if( n == NULL){
         return;
    }
    else{
        int V = n -> e.H * n -> e.D * n -> e.W;
        inorderRec(n -> left);
        printf("Box(H = %d, W = %d, D = %d, V = %d, O = %s)\n", n -> e.H, n -> e.W, n -> e.D, V, n -> e.O);
        inorderRec(n -> right);
    }
}

void inorder(AVL*t){
    inorderRec(t -> root);
}

void preorderRec(AVLnode*n){
    if(n == NULL){
        return;
    }
    else{
        int V = n -> e.H * n -> e.D * n -> e.W;
        printf("Box(H = %d, W = %d, D = %d, V = %d, O = %s)\n", n -> e.H, n -> e.W, n -> e.D, V, n -> e.O);
        preorderRec(n -> left);
        preorderRec(n -> right);
    }
}

void preorder(AVL*t){
    preorderRec(t -> root);
    
}


void postorderRec(AVLnode* n){
    if(n == NULL){
        return;
    }
    else{
        int V = n -> e.H * n -> e.D * n -> e.W;
        postorderRec(n -> left);
        postorderRec(n -> right);
        printf("Box(H = %d, W = %d, D = %d, V = %d, O = %s)\n", n -> e.H, n -> e.W, n -> e.D, V, n -> e.O);
    }
}

void postorder(AVL* t){
    postorderRec(t -> root);
}


AVL * newAVL(){
    AVL* avl = (AVL*)malloc(sizeof(AVL));
    avl -> root = NULL;
    return avl;
}







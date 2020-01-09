#include "BST.h"


int comp(Element left, Element right){
    int leq = strcmp(left.last, right.last);
    int fcmp;
    if(leq == 0){
        fcmp = strcmp(left.first, right.first);
        if(fcmp < 0){
            return -1;
        }
        else if(fcmp > 0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(leq < 0){
        return -1;
    }
    else{
        return 1;
    }
    
}


// Creates new Bstnode 

BSTnode* createNode(Element e){
    BSTnode* node = (BSTnode*)malloc(sizeof(BSTnode));
    node -> left = NULL;
    node -> right = NULL;
    node -> e = e;
    return node;
}


// Inorder rec. function

void inorderRec(BSTnode *n){
    if( n == NULL){
        return;
    }
    else{
        inorderRec(n -> left);
        printf("\t%s, %s\n", n -> e.last, n -> e.first);
        inorderRec(n -> right);
    }
}

void inorderFunc(BSTree*t){
    inorderRec(t -> root);
}


//nodeInsert

BSTnode * nodeInsert(BSTnode* n, BSTnode* i){
    if(n == NULL){
        return i;
        
    }
    else{
        int cmp = comp(n -> e, i -> e);
        if(cmp == -1){
            n -> right = nodeInsert(n -> right, i);
            
        }
        else if(cmp >= 0){
            n -> left = nodeInsert(n -> left, i);
        }
        else{
            return n;
        }
    }
}


// Preorder rec. function

void preorderRec(BSTnode*n){
    if(n == NULL){
        return;
    }
    else{
        printf("\t%s, %s\n", n -> e.last, n -> e.first);
        preorderRec(n -> left);
        preorderRec(n -> right);
    }
}

void preorderFunc(BSTree*t){
    preorderRec(t -> root);
    
}

// Postorder function

void postorderRec(BSTnode* n){
    if(n == NULL){
        return;
    }
    else{
        postorderRec(n -> left);
        postorderRec(n -> right);
        printf("\t%s, %s\n", n -> e.last, n -> e.first);
    }
}

void postorderFunc(BSTree* t){
    postorderRec(t -> root);
}


// Insert function

BSTnode* recInsert(BSTnode*n, Element e){
 // Element e = n -> e;
  if(n == NULL){
    BSTnode* newNode = createNode(e);
    return newNode;
    
  }
  else{
    int cmp = comp(e, n ->e);
    if(cmp == -1){
        n -> left = recInsert(n -> left, e);
    }
    else if(cmp == 1){
        n -> right = recInsert(n -> right, e);
    }
    else{
        n -> left = recInsert(n -> left, e);
    }
   }
   return n;
}


void insertFunc(BSTree* t, Element e){
   t -> root = recInsert(t -> root, e);

  
}

// Remove function

BSTnode* removeFunc(BSTnode* n, Element e, int * i){
    if(n == NULL){
        return n;
    }
    if(comp(e, n -> e) == 1 ){
        n -> right = removeFunc(n -> right, e, i);

    }
    else if(comp(e, n -> e) == -1){
        n -> left = removeFunc(n -> left, e, i);
    
    }
    else{
        
        if(n -> left == NULL && n -> right == NULL){
            free(n);
            return NULL;
        }
        else if(n -> left != NULL && n -> right == NULL){
            BSTnode * temp = n -> left;
            free(n);
            return temp;
        }
        else if(n -> right != NULL && n -> left == NULL){
            BSTnode * temp = n -> right;
            free(n);
            return temp;
        }
        else{
            int i =0;
            int c = comp(n -> left -> e, n -> right -> e);
            if(c >= 0){
                n -> left -> left - nodeInsert(n -> left -> left, n -> right);
                BSTnode * temp = n -> left;
                free(n);
                i++;
                return temp;
            }
            else{
                n -> right -> right = nodeInsert(n -> right -> right, n -> left);
                BSTnode * temp = n -> right;
                free(n);
                i++;
                return temp;
                
            }
        }
    }
    return n;
    
}


BSTnode * recRemoveAll(BSTnode* n, char lastName[], int *i){
    if(n == NULL){
        return NULL;
    }
    else {
        n -> left = recRemoveAll(n -> left, lastName, i);
        n -> right = recRemoveAll(n -> right, lastName, i);
        if(strcmp(n -> e.last, lastName) == 0){
            if(n -> left == NULL && n -> right == NULL){
                free(n);
                return NULL;
                
            }
            else if(n -> left != NULL && n -> right == NULL){
                
                BSTnode * temp = n -> left;
                free(n);
                return temp;
            }
            else if(n -> right != NULL && n -> left == NULL){
                BSTnode * temp = n -> right;
                free(n);
                return temp;
            }
            else{
                
                int c = comp(n -> left -> e, n -> right -> e);
                if(c >= 0){
                    n -> left -> left = nodeInsert(n -> left -> left, n -> right);
                    BSTnode * temp = n -> left;
                    free(n);
                    (*i)++;
                    return temp;
                }
                else{
                    n -> right -> right = nodeInsert(n -> right -> right, n -> left);
                    BSTnode * temp = n -> right;
                    free(n);
                    (*i)++;
                    return temp;
                
                }
            }
            
        }
    }
    return n;
}



// Destroy functino

BSTnode* recdestroy(BSTnode*n){
    if(n == NULL){
        return n;
    }
    else{
        recdestroy(n -> left);
        recdestroy(n -> right);
        free(n);
    }
    return n;
}

void destroyFunc(BSTree* t){
    t -> root = recdestroy(t -> root);
    free(t -> root);
    free(t);
}

//List Fuction
void  ListLast( BSTnode* n, char last[]){
    if( n == NULL){
        return;
    }
    else if( strcmp(n -> e.last, last)!=0){
        return;
    }
    else{
        ListLast(n -> left, last);
        printf("\t%s\n", n -> e.first);
        ListLast(n -> right, last);
    }
}


// Constructor that creates the tree

BSTree * newBSTree(){
    BSTree* bst = (BSTree*)malloc(sizeof(BSTree));
    bst -> root = NULL;
    bst -> inorder = inorderFunc;
    bst -> preorder = preorderFunc;
    bst -> insert = insertFunc;
    bst -> remove = removeFunc;
    bst -> postorder = postorderFunc;
    bst -> destroy = destroyFunc;
    return(BSTree*)bst;
}
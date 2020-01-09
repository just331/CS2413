#ifndef ___AVL_HEADER__
#define ___AVL_HEADER__
#include "stdheader.h"

struct _Box{
   char O[21];
   int H;
   int W;
   int D;
   int V;
};

typedef struct _Box Element;

struct _AVL_node{
    struct _AVL_node *right;
    struct _AVL_node *left;
    Element e;
    int height;
};
typedef struct _AVL_node AVLnode;


struct _AVL_tree{
    AVLnode *root;
    
};
typedef struct _AVL_tree AVL;




AVL* newAVL();
void postorder(AVL*);
void preorder(AVL*);
void inorder(AVL*);
AVLnode* removeNode(AVLnode*, int, bool*);
int count(AVLnode*, int);
AVLnode* add(AVLnode*, Element);
int compare(int, int);
void removeAll(AVL*, int);

#endif

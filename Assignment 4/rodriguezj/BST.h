#ifndef ___BST_HEADER__
#define ___BST_HEADER__

#include "stdheader.h"
#include "element.h"


struct _node{
  Element e;
  struct _node *right;
  struct _node *left;
};

typedef struct _node BSTnode;


typedef struct _bstree_interface BSTree;
struct _bstree_interface{
  void (*insert)(BSTree *, Element);
  BSTnode * (*remove)(BSTnode *, Element, int*);
  void (*inorder)(BSTree*);
  void (*preorder)(BSTree*);
  void (*postorder)(BSTree*);
  void (*destroy)(BSTree*);
  BSTnode * root;
};





/* newBSTree: () --> BSTree*   // CONSTRUCTOR
*  Allocate the space, format an empty tree
*  and return the interface
*/
BSTree * newBSTree();
BSTnode * recRemoveAll(BSTnode*, char[], int*);
void ListLast(BSTnode*, char[]);
//BSTnode * recRemoveAllFull(BSTnode*, Element, int *);
#endif

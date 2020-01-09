#ifndef ___BSTREE_HEADER__
#define ___BSTREE_HEADER__

#include "element.h"

typedef struct _bstree_interface BSTree;
struct _bstree_interface{
  BSTree * (*insert)(BSTree *, Element);
  BSTree * (*remove)(BSTree *, Element, int*);
  void * (*inorder) (BSTree *, void*, void* (*f)(void*, Element));
  void * (*preorder) (BSTree *, void*, void* (*f)(void*, Element));
  void * (*postorder) (BSTree *, void*, void* (*f)(void*, Element));
  void (*destroy)(BSTree*);
};


#endif

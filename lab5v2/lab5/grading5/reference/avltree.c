#include"avltree.h"
#include"trackedmemory.h"

typedef struct _avlnode anode;
struct _avlnode{
  Element e;
  anode * left; 
  anode * right;
  size_t height;
};

typedef struct _avltree AVL;
struct _avltree {
  BSTree bsti;
  anode * root;
};

BSTree * AVLinsert(BSTree*, Element);
BSTree * AVLremove(BSTree*, Element, int*);
void * AVLinorder(BSTree*,void*,void*(*f)(void*,Element));
void * AVLpreorder(BSTree*,void*,void*(*f)(void*,Element));
void * AVLpostorder(BSTree*,void*,void*(*f)(void*,Element));
void AVLdestroy(BSTree*);

BSTree * newAVLTree(){
  AVL *t = (AVL*)MALLOC(sizeof(AVL));
  t->bsti.insert = AVLinsert;
  t->bsti.remove = AVLremove;
  t->bsti.inorder = AVLinorder;
  t->bsti.preorder = AVLpreorder;
  t->bsti.postorder = AVLpostorder;
  t->bsti.destroy = AVLdestroy;
  t->root = NULL;
  return (BSTree*)t;
}

anode* recinsert(anode*, Element e);
anode* recremove(anode*, Element e, int*);
void*  inorderfold(anode*, void*, void*(*f)(void*, Element));
void*  preorderfold(anode*, void*, void*(*f)(void*, Element));
void*  postorderfold(anode*, void*, void*(*f)(void*, Element));

BSTree * AVLinsert(BSTree* bst, Element e){
  //printf("Inserting %s\n", e.O);
  AVL*t = (AVL*)bst;
  t->root = recinsert(t->root, e);
  return bst;
}

BSTree * AVLremove(BSTree*bst, Element e, int*i){
  AVL*t =(AVL*)bst;
  t->root = recremove(t->root, e, i);
  return bst;
}

void * AVLinorder(BSTree*bst,void*a,void*(*f)(void*,Element)){
  AVL*t =(AVL*)bst;
  return inorderfold(t->root, a, f);
}
void * AVLpreorder(BSTree*bst,void*a,void*(*f)(void*,Element)){
  AVL*t =(AVL*)bst;
  return preorderfold(t->root, a, f);
}
void * AVLpostorder(BSTree*bst,void*a,void*(*f)(void*,Element)){
  AVL*t =(AVL*)bst;
  return postorderfold(t->root, a, f);
}

void anodedestroy(anode* n){
  if(n!= NULL){
    anodedestroy(n->left);
    anodedestroy(n->right);
    FREE(n);
  }
}

void AVLdestroy(BSTree* bst){
  AVL*t =(AVL*)bst;
  anodedestroy(t->root);
  FREE(bst);
}
static inline size_t max(size_t a, size_t b){
 if(a < b) return b;
 return a;
}

size_t  Height(anode*n){
 if(n == NULL)return 0;
 return n->height;
}

void RecalcHeight(anode*n){
  if(n == NULL) return;
  n->height = max(Height(n->left), Height(n->right)) +1;
  //printf("RH: O= %s, H =%lu\n", n->e.O, Height(n));
}


anode * RotateLeft(anode *n);
anode * RotateRight(anode *n);

anode * Rebalance(anode *n){
  if(n == NULL) return n;
  //printf("Rebalance of %s\n", n->e.O);
  if(Height(n->left) > Height(n->right)+1){
    if(Height(n->left->right) > Height(n->left->left))
      n->left = RotateLeft(n->left);
    return RotateRight(n);
  } else if(Height(n->right) > Height(n->left) +1){
    if(Height(n->right->left) > Height(n->right->right))
      n->right = RotateRight(n->right);
    return RotateLeft(n);
  }
  RecalcHeight(n);
  return n;
}
anode * RotateLeft(anode *n){
  if(n == NULL || n->right == NULL)return n;
  //printf("RotateLeft %s\n", n->e.O);
  anode * newroot = n->right;
  n->right = newroot->left;
  newroot->left = n;
  RecalcHeight(n);
  RecalcHeight(newroot);
  return newroot;
}
anode * RotateRight(anode *n){
  //printf("RotateRight %s\n", n->e.O);
  if(n == NULL || n->left == NULL)return n;
  anode * newroot = n->left;
  n->left = newroot->right;
  newroot->right = n;
  RecalcHeight(n);
  RecalcHeight(newroot);
  return newroot;
}

anode* newANode(Element e, anode*left, anode*right){
  anode* n = (anode*)MALLOC(sizeof(anode));
  n->e = e;
  n->left = left;
  n->right = right;
  n->height = 1;
  return n;
}

anode* recinsert(anode*n, Element e){
  if(n == NULL)return newANode(e, NULL, NULL);
  int comp = eCompare(e, n->e);
  if( comp <= 0)
    n->left = recinsert(n->left, e);
  else
    n->right = recinsert(n->right, e);
  return Rebalance(n);
}

anode* recremoveHelp(anode * n, anode*r){
 if(n== NULL) return n;
 if(n->right == NULL){
   r->e = n->e;
   anode * left = n->left;
   FREE(n);
   return left;
 }else {
   n->right = recremoveHelp(n->right, r);
 }
 return Rebalance(n);
}

anode* recremove(anode*n, Element e, int*i){
  if(n == NULL)return n;
  int comp = eCompare(e, n->e);
  if( comp < 0)
    n->left = recremove(n->left, e, i );
  else if(comp > 0)
    n->right = recremove(n->right, e,i);
  else {
    (*i)++;
    if(n->left == NULL){ 
      anode*right = n->right;
      FREE(n);
      return right;
    }else {
      n->left = recremoveHelp(n->left, n);
    }
  }
  return Rebalance(n);
}

void*  inorderfold(anode*n, void*a, void*(*f)(void*, Element)){
  if(n == NULL)return a;
  a = inorderfold(n->left, a,f);
  a = f(a, n->e);
  return inorderfold(n->right,a,f);
}


void*  preorderfold(anode*n, void*a, void*(*f)(void*, Element)){
  if(n == NULL)return a;
  a = f(a, n->e);
  a = preorderfold(n->left, a,f);
  return preorderfold(n->right,a,f);
}

void*  postorderfold(anode*n, void*a, void*(*f)(void*, Element)){
  if(n == NULL)return a;
  a = postorderfold(n->left, a,f);
  a = postorderfold(n->right,a,f);
  return f(a, n->e);
}

#include"multisetbstree.h"
#include"trackedmemory.h"


typedef struct _bst_multi_set BMS;
struct _bst_multi_set{
   MultiSet mi;
   BSTree * bst;
   Element toCount;// Only used for counting purposes
   size_t count;// Only used for counting purposes
};


MultiSet * BMSadd(MultiSet*, Element);
MultiSet * BMSremove(MultiSet*, Element);
MultiSet * BMSremoveAll(MultiSet*, Element);
int BMScontains(MultiSet *, Element);
size_t BMScount(MultiSet *, Element);
void BMSdestroy(MultiSet *);


MultiSet * newBSTMultiSet(BSTree * bst){
   BMS *m = (BMS*)MALLOC(sizeof(BMS));
   m->mi.add = BMSadd;
   m->mi.remove = BMSremove;
   m->mi.removeAll = BMSremoveAll;
   m->mi.contains = BMScontains;
   m->mi.count = BMScount;
   m->mi.destroy = BMSdestroy;
   m->bst = bst;
   return (MultiSet*)m;
}


MultiSet * BMSadd(MultiSet* ms, Element e){
  BMS * bms = (BMS*)ms;
  bms->bst->insert(bms->bst, e);  //add the element to the underlying BST
  return ms;
}

MultiSet * BMSremove(MultiSet* ms, Element e){
  BMS * bms = (BMS*)ms;
  int deleted =0;
  bms->bst->remove(bms->bst, e, &deleted);  
  //remove an element from the underlying BST
  return ms;
}

MultiSet * BMSremoveAll(MultiSet* ms, Element e){
  BMS * bms = (BMS*)ms;
  int deleted =1;
  while(deleted){
    deleted = 0;
    bms->bst->remove(bms->bst, e, &deleted);  
  }
  //remove an element from the underlying BST
  return ms;
}

int BMScontains(MultiSet* ms, Element e){
  if(ms->count(ms, e) >0) return 1;
  return 0;
}


void * countElements(void * a, Element e){
  //Expecting *a to be of type BMS* which stores the element being counted and the count. 
  BMS* bms = (BMS*)a;
  if(eCompare(bms->toCount, e) == 0)
    bms->count++;  //increment the count for a match
  return a;
}

size_t BMScount(MultiSet* ms, Element e){
  BMS * bms = (BMS*)ms;
  bms->count = 0;
  bms->toCount = e;
  bms->bst->inorder(bms->bst, bms, countElements);
  return bms->count;
}


void BMSdestroy(MultiSet *ms){
  FREE(ms);
}



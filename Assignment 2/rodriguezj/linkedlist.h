#ifndef __linkedlist_h_
#define __linkedlist_h_

#include "list.h"
#include <stdlib.h>

typedef struct _llnode llnode;

struct _llnode{
    void * e;
    llnode * next;
};


struct _linked_list{
    List li;
    llnode * first;
    llnode * last;
    size_t size;
};

typedef struct _linked_list LinkedList;

List * LLPrepend(List*, void*);
List * LLAppend(List*, void*);
List * LLRemoveFirst(List*, void**);
List * LLRemoveLast(List*, void**);
List * LLSet(List*, size_t, void*);
List * LLGet(List*, size_t, void**);
List * LLInsert(List*, size_t, void*);
List * LLRemove(List*, size_t, void**);
List * newLinkedList();
llnode * newLLNode(void *, llnode *);
llnode * newGetNode(llnode *, List* size_t);
size_t LLSize(List*);
//ist * LLSort(List*, int (*comp)(void*, void*));
void * LLFold(List*, void*, void* (*f)(void*,void*));
void LLDestroy(List*);



#endif

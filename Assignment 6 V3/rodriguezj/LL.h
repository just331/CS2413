#ifndef _LINKEDLIST__H_
#define _LINKEDLIST__H_

#include "map.h"
#include "my_size_t.h"

typedef struct _llNode Node;
struct _llNode{
  Key k;
  Value v;
  Node *next;
};

typedef struct _linked_list LL;
struct _linked_list{
  Map mi;
  Node *listHead;
  char flag;
};


Map *LLadd(Map *, Key , Value );
Map *LLremove(Map *, Key );
Map *LLlookup(Map *, Key , Value **);
void LLdestroy(Map *);
void freeLL(Node *);

Map *newLinkedList(char flag);

#endif

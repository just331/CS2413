#include "LL.h"
#include "trackedmemory.h"


Map * newLinkedList(char flag){
  LL *l = (LL*)MALLOC(sizeof(LL));
  l->mi.add = LLadd;
  l->mi.remove = LLremove;
  l->mi.lookup = LLlookup;
  l->mi.destroy = LLdestroy;

  l->listHead = NULL;
  l->flag = flag;

  return (Map*)l;
}

Map *LLadd(Map* m, Key k, Value v){
  
  LL *l = (LL*)m;

  char keyText[21], valueText[21];
  printKey(k, keyText, 21);
  printValue(v, valueText, 21);

  Node *newNode = (Node*)MALLOC(sizeof(Node));
  newNode->k = k;
  newNode->v = v;

  if(l->flag)
    printf("adding %s %s at 0\n", keyText, valueText);

  newNode->next = l->listHead;
  l->listHead = newNode;

  return (Map*)l;
}

Map *LLlookup(Map *m, Key k, Value **v){
  LL *l = (LL*)m;

  char keyText[21];
  Node *currNode;
  int i = 0;

  printKey(k, keyText, 21);
  currNode = l->listHead;

  if(currNode == NULL)
    *v = NULL;
  else{
    while((currNode != NULL) && (keyCompare(currNode->k, k) != 0)){
      currNode = currNode->next;
      i++;
    }
  }

  if(currNode == NULL)
    *v = NULL;

  else
    **v = currNode->v;

  if(l->flag && *v){
    char valueText[21];
    printValue(**v, valueText, 21);
    printf("lookup %s at %d found %s\n", keyText, i, valueText );
  }

  else if(l->flag)
    printf("lookup %s undefined\n", keyText);

  return (Map*)l;
}

Map * LLremove(Map *m, Key k){
  printf("Cannot remove key.\n" );
  return m;
}


void LLdestroy(Map *m){
  LL *l = (LL*)m;
  freeLL(l->listHead);
  FREE(l);
  return;
}

void freeLL(Node *n){
  Node *currNode = n;

  if(n->next == NULL)
    FREE(currNode);
  else{
    freeLL(currNode->next);
    FREE(currNode);

  }

  return;
}

#include "queuelistwrapper.h"
#include "trackedmemory.h"




Queue* QueueListWrapper(List *l){
  QLW *q = (QLW*)MALLOC(sizeof(QLW));
  q -> qi.enqueue = QLWEnqueue;
  q -> qi.dequeue = QLWDequeue;
  q -> qi.peek = QLWPeek;
//  q -> qi.size = QLWSize;
  q -> qi.destroy = QLWDestroy;
  q -> l = l;
/*  
  q -> l -> append = LLAppend;
  q -> l -> removefirst = LLRemoveFirst;
  q -> l -> get = LLGet;
  q -> l -> size = LLSize;*/
  return (Queue*)q;
}

Queue * QLWEnqueue(Queue *q, void *e){
  QLW * qi = (QLW*)q;
  qi -> l -> append(qi -> l, e);
  return(q);
}
Queue * QLWDequeue(Queue *q, void **e){
  QLW * qi = (QLW*)q;
  *e = NULL;
  qi -> l -> removefirst(qi -> l, e);
  return(q);
}

Queue * QLWPeek(Queue * q, void **e){
  QLW * qi = (QLW*)q;
  qi -> l -> get(qi -> l,0,e);
  return(q);
}

/*size_t QLWSize(Queue*q){
  QLW * qi = (QLW*)q;
  return(qi -> size);
}*/

void QLWDestroy(Queue*q){
  QLW * qi = (QLW*)q;
  FREE(qi);
}
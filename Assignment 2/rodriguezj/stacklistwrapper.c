#include "stacklistwrapper.h"
#include "trackedmemory.h"


Stack* StackListWrapper(List *l){
  SLW *s = (SLW*)MALLOC(sizeof(SLW));
  s -> si.push = SLWPush;
  s -> si.pop = SLWPop;
  s -> si.peek = SLWPeek;
//  s -> si.size = SLWSize;
  s -> si.destroy = SLWDestroy;
  s -> l = l;
  
/*  s -> l -> prepend = LLPrepend;
  s -> l -> removefirst = LLremovefirst;
  s -> l -> get = LLget;
  s -> l -> size = LLSize;
  */
  /*LinkedList * LL = (LinkedList*)l;
  llnode * top = LL -> first;
  */
  return (Stack*)s;
  

}

Stack * SLWPush(Stack *s, void *e){
  SLW * si = (SLW*)s;
  si -> l -> prepend(si -> l, e);
  return(s);
}

Stack * SLWPop(Stack *s, void **e){
  SLW * si = (SLW*)s;
  *e = NULL;
  si -> l -> removefirst(si -> l, e);
  return(s);
}

Stack * SLWPeek(Stack * s, void **e){
  SLW * si = (SLW*)s;
  si -> l -> get(si -> l,0,e);
  return(s);
}

/*size_t SLWSize(Stack*s){
  SLW * si = (SLW*)s;
  return si -> size;
  
}*/

void SLWDestroy(Stack*s){
  SLW * si = (SLW*)s;
  FREE(si);
}
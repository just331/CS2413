#ifndef __stack_list_wrapper_h_
#define __stack_list_wrapper_h_

#include "stack.h"
#include "list.h"

struct _stacklistwrapper{
    Stack si;
    List * l;
    
};

typedef struct _stacklistwrapper SLW;



Stack* StackListWrapper(List *);
Stack* SLWPeek(Stack*, void **);
Stack* SLWPush(Stack*, void*);
Stack* SLWPop(Stack*, void**);
//size_t SLWSize(Stack*);
void SLWDestroy(Stack*);

#endif

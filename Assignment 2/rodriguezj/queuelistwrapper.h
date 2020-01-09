#ifndef __queue_list_wrapper_h_
#define __queue_list_wrapper_h_

#include "queue.h"
#include "list.h"

struct _queuelistwrapper{
    Queue qi;
    List *l;
    
};

typedef struct _queuelistwrapper QLW;

Queue* QueueListWrapper(List *);
Queue* QLWEnqueue(Queue*, void*);
Queue* QLWDequeue(Queue*,void**);
Queue* QLWPeek(Queue*, void**);
//size_t QLWSize(Queue*);
void QLWDestroy(Queue*);


#endif

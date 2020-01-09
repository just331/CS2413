#include <stdlib.h>
#include "trackedmemory.h"
#include "linkedlist.h"


List * newLinkedList(){
	LinkedList * LL = (LinkedList*)MALLOC(sizeof(LinkedList));
	LL -> li.prepend = LLPrepend;
	LL -> li.append = LLAppend;
	LL -> li.remove = LLRemove;
	LL -> li.removefirst = LLRemoveFirst;
	LL -> li.removelast = LLRemoveLast;
	LL -> li.set = LLSet;
	LL -> li.get = LLGet;
	LL -> li.insert = LLInsert;
	LL -> li.destroy = LLDestroy;
//	LL -> li.sort = LLSort;
	LL -> li.fold = LLFold;
	LL -> li.size = LLSize;
	LL -> first = NULL;
	LL -> last = NULL;
	LL -> size = 0;
	return (List*)LL;
	
}

llnode * newLLNode(void * e, llnode * next){
	llnode * n = (llnode *)MALLOC(sizeof(llnode));
	n -> e = e;
	n -> next = next;
	return n;
}

llnode * LLGetNode(llnode *n, size_t i){
	if(n == NULL)
		return NULL;
	if(i == 0)
		return n;
	return LLGetNode(n -> next, i-1);
}

List * LLInsert(List * l, size_t index, void * e){
	LinkedList * LL = (LinkedList*)l;
	if(index >= LL -> size)
		return LLAppend(l,e);
	if(index == 0)
		return LLPrepend(l,e);
	llnode * n = LLGetNode(LL -> first, index -1);
	n -> next = newLLNode(e, n -> next);
	return(l);
	
} 
List * LLRemove(List * l, size_t index, void **e){
	LinkedList * LL =(LinkedList*)l;
	if(index >= LL -> size)
		return l;
	if(index == LL -> size -1)
		return LLRemoveLast(l, e);
	if(index == 0)
		return LLRemoveFirst(l, e);
	llnode * prior = LLGetNode(LL -> first, index -1);
	llnode * n = prior -> next;
	*e = n -> e;
	prior -> next = n -> next;
	FREE(n);
	return l;
	
	
	
}

List * LLPrepend(List* l,void * e ){
	LinkedList *LL = (LinkedList*)l;
	llnode* ln = (llnode*)MALLOC(sizeof(llnode));
	ln -> next = LL -> first;
	LL -> first = ln;
	if(LL -> last == NULL)
		LL -> last = LL -> first;
	LL -> size ++;
	return l;
}

List * LLAppend(List* l, void *e){
	LinkedList *LL = (LinkedList*)l;
	llnode* ln = (llnode*)MALLOC(sizeof(llnode));
	ln -> e = e;
	ln -> next = NULL;
	LL -> size++;
	if(LL -> first == NULL)
		LL -> first = ln;
	else
		LL -> last -> next = ln;
	LL -> last = ln;
	return l;
	
}

List * LLRemoveFirst(List * l, void **e){
	LinkedList *LL = (LinkedList*)l;
	if(LL -> size ==0)
		return NULL;
	else{
		* e = LL -> first -> e;
		llnode* t = LL -> first;
		LL-> first = LL -> first -> next;
		FREE(t);
		LL -> size --;
	}
	return l;
	
}

List * LLRemoveLast(List* l, void **e){
	LinkedList * LL = (LinkedList*)l;
	if(LL -> size == 0)
		return NULL;
		
	if(LL -> first == LL -> last){
		LL -> first = NULL;
		LL -> last = NULL;
		
	}
	else{
		/*llnode* t = LL -> last;
		while(t -> next != LL -> last){
		*/
		
		
	llnode* prior = LLGetNode(LL ->first, (LL -> size -2));
	llnode *temp = LL ->last;

	*e = temp -> e;
	LL -> last = prior;
	FREE(temp);
	LL -> size --;


		
	}
	return l;
	
}



List * LLGet(List* l, size_t i, void ** e){
	LinkedList *LL = (LinkedList*)l;
	if( i > LL -> size)
		*e =NULL;
	else{
		*e  = LLGetNode(LL -> first, i);
	}
	return l;
}



/*List * LLSort(List*l, int (*comp)(void*, void*)){
  LinkedList * LL = (LinkedList *) l;
  return l;
}*/

List* LLRecFold(llnode* ln, void*a, void* (*f)(void*, void*)){
	if(ln == NULL){
		return a;
	}
	else{
		return (LLRecFold(ln -> next, f(a, ln ->e), f));
	}
	
}

void* LLFold(List*l, void*a, void* (*f)(void*,void*)){
  LinkedList * LL = (LinkedList*)l;
  return (LLRecFold(LL -> first, a, f));
  
}
size_t LLSize(List*l){
	LinkedList* LL= (LinkedList*)l;
	return LL -> size;
}

List* LLSet(List *l, size_t i, void *e){
	LinkedList* LL = (LinkedList*)l;
	if( i >= LL -> size){
		return LLAppend(l,e);
		LL -> size = LL -> size + 1;
	}
	else{
		int index = 0;
		llnode * temp = LL -> first;
		while(index != i){
			temp = temp -> next;
			index ++;
		}
		temp -> e = e;
	}
	
	return l;	
}

void LLDestroy(List*l){
	LinkedList * LL = (LinkedList*)l;
	FREE(LL);
}


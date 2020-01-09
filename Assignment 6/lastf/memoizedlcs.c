#include<stdio.h>
#include<string.h>
#include"memoizedlcs.h"
#include"map.h"
#include"hashmap.h"
#include"trackedmemory.h"




size_t MLCS(LCS*, size_t, size_t);
size_t MMemUsed(LCS*);
void MDestroy(LCS *);

typedef struct _htable_entry hentry;
struct _htable_entry{
    size_t e;
    char exists;
};

typedef struct _lcs_memo LCSMemo;
//opaque table structure
struct _lcs_memo{
   LCS li;
   Map * M; //map for memoization
   char* s1;  //pointers to each string
   char* s2;
   size_t s1len;  //lengths of strings
   size_t s2len;
   size_t memused;
   char flag;
};


/* Returns An LCS object implemented as a memoized function.
 * Implements LCS interface. 
 * Everything Needed To Compute A Solution
 */
LCS * memoizedlcs(char * f1, char * f2, char flag){
    size_t mem_before = getMemoryUsage();
    LCSMemo * t = (LCSMemo*)MALLOC(sizeof(LCSMemo));
    t -> li.lcs = MLCS;
    t -> li.destroy = MDestroy;
    t -> li.memoryusage = MMemUsed;
    t -> s1 = f1;
    t -> s2 = f2;
    t -> s1len = strlen(f1);
    t -> s2len = strlen(f2);
    t -> flag = flag;
    
    long i,j;
    //Need to fill table 
    
    t -> M = newHashMap(flag);
    
    
    size_t mem_after = getMemoryUsage();
    t -> memused = mem_after - mem_before;
    MLCS((LCS*)t, 0,0);
    
    
   return(LCS*)t;
}

//Implements lcs interface function. 
//Lookup the index values in the LCS table.
//calculate it if it does not exist in the table 
size_t MLCS(LCS*l, size_t i, size_t j){
  LCSMemo * m = (LCSMemo*)l;
  Key k;
  k.i = i;
  k.j = j;
  Value v, *v_ptr;
  v_ptr = &v;
  m -> M -> lookup(k, &v_ptr);
  if(v_ptr != NULL)
    return V;
  
  
  m -> M -> add(m -> M, k, v);
  return v;
}

//return memory used in construction. 
size_t MMemUsed(LCS*l){
  LCSMemo*t = (LCSMemo*)l;
  return t -> memused;
}

//free all memory allocated in the constructor. 
void MDestroy(LCS *l){
    LCSMemo* t = (LCSMemo*)l;
    if(t){
        size_t i;
        for(i = 0; i < t -> s1len; i++){
            FREE(t -> A[i]);
        }
        FREE(t -> A);
        FREE(t);
    }
  
}




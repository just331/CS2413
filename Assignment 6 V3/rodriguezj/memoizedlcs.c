#include<stdio.h>
#include<string.h>
#include"memoizedlcs.h"
#include"map.h"
#include"hashmap.h"
#include"trackedmemory.h"
#include"LL.h"

my_size_t MLCS(LCS*, my_size_t, my_size_t);
my_size_t MMemUsed(LCS*);
void MDestroy(LCS *);

typedef struct _lcs_memo LCSMemo;
//opaque table structure
struct _lcs_memo{
   LCS li;
   Map * M; //map for memoization
   char* s1;  //pointers to each string
   char* s2;
   my_size_t s1len;  //lengths of strings
   my_size_t s2len;
   my_size_t memused;
};


/* Returns An LCS object implemented as a memoized function.
 * Implements LCS interface.
 * Everything Needed To Compute A Solution
 */
LCS * memoizedlcs(char * f1, char * f2, char flag){
   LCSMemo * m = (LCSMemo*)MALLOC(sizeof(LCSMemo));
   //IMPLEMENT HERE
   my_size_t mem_before = getMemoryUsage();
   m->li.lcs = MLCS;
   m->li.memoryusage = MMemUsed;
   m->li.destroy = MDestroy;
   m->s1 = f1;
   m->s2 = f2;
   m->s1len = strlen(f1);
   m->s2len = strlen(f2);

   //Mape Interface
   m->M = newHashMap(flag);
   my_size_t mem_after = getMemoryUsage();
   m->memused = mem_after - mem_before;

   MLCS((LCS*)m, 0, 0);

   return (LCS*)m;
}

//Lookup the index values in the LCS table.
//calculate it if it does not exist in the table
my_size_t MLCS(LCS*l, my_size_t i, my_size_t j){
  LCSMemo * m = (LCSMemo*)l;
  Key k;
  Value v, *v_ptr;

  k.i = i, k.j = j;
  v_ptr = &v;

  m->M->lookup(m->M, k, &v_ptr);

  //If Value does not exist
  if(v_ptr != NULL)
    return v;

  //Calculate the value
  if(i > m->s1len || j > m->s2len) return 0;

  if(i < 0 || j < 0) return 0;

  if(m->s1[i] == m->s2[j]){ 
    if(i == m->s1len-1 || j == m->s2len-1) 
      v = 1;
    else
      v = 1 + MLCS(l, i+1, j+1);
  }

  else{//No Match
    if(i == m->s1len-1 && j == m->s2len-1)
      v = 0;
    else if(i == m->s1len-1)
      v = MLCS(l, i, j+1);
    else if(j == m->s2len-1)
      v = MLCS(l, i+1, j);
    else
      v = max(MLCS(l, i+1, j), MLCS(l, i, j+1));
  }

  m->M = m->M->add(m->M, k, v);

  return v;
}

//return memory used in construction.
my_size_t MMemUsed(LCS*l){
  LCSMemo* t = (LCSMemo*)l;
  //DEPRECATED, DO NOT IMPLEMENT
  return 0;
}

//free all memory allocated in the constructor.
void MDestroy(LCS *l){
  LCSMemo * m = (LCSMemo*)l;
  if(m){
    m->M->destroy(m->M);
    FREE(m);
  }
}

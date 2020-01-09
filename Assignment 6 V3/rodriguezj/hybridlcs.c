#include <string.h>
#include <stdio.h>
#include "trackedmemory.h"
#include "hybridlcs.h"


my_size_t HLCS(LCS*, my_size_t, my_size_t);
my_size_t HMemUsed(LCS*);
void HDestroy(LCS *);

typedef struct _htable_entry hentry;
struct _htable_entry{
  my_size_t e;
  char exists;
};

typedef struct _lcs_hybrid LCSHybrid;
//opaque table structure
struct _lcs_hybrid{
   LCS li;
   hentry ** A; //pointer to table
   char* s1;  //pointers to each string
   char* s2;
   my_size_t s1len;  //lengths of strings
   my_size_t s2len;
   my_size_t memused;
};


/* Returns An LCS object implemented as a lookup table.
 * Implements LCS interface.
 * Everything Needed To Compute A Solution
 */
LCS * hybridlcs(char * f1, char * f2){
   my_size_t mem_before = getMemoryUsage();
   LCSHybrid * t = (LCSHybrid*)MALLOC(sizeof(LCSHybrid));
   t->li.lcs = HLCS;
   t->li.memoryusage = HMemUsed;
   t->li.destroy = HDestroy;
   t->s1 = f1;
   t->s2 = f2;
   t->s1len = strlen(f1);
   t->s2len = strlen(f2);
   //printf("Calculating Table... %u %u\n", t->s1len, t->s2len);

   long i,j;

   //Allocate Table Space
   t->A = (hentry**)MALLOC(sizeof(hentry*)*t->s1len);
   for(i = 0; i < t->s1len; i++)
     t->A[i] = (hentry*)CALLOC(sizeof(hentry),t->s2len);
   //printf("Table Allocated\n");

   //indicate memory used
   my_size_t mem_after = getMemoryUsage();
   t->memused = mem_after - mem_before;
   //Fill In Table
   HLCS((LCS*)t, 0,0);
   //Return Table
   return (LCS*)t;
}

//Lookup the index values in the LCS table.
//calculate it if it does not exist in the table
my_size_t HLCS(LCS*l, my_size_t i, my_size_t j){
  LCSHybrid * t = (LCSHybrid*)l;
  if(t->A[i][j].exists)
    return t->A[i][j].e;  //already calculated
  //need to calculate value.
  t->A[i][j].exists = 1;  //value will exist now
  if(t->s1[i] == t->s2[j]){ //match
    if(i == t->s1len -1 || j == t->s2len-1) //base case
       t->A[i][j].e = 1;  //one of i or j cannot advance
    else
       t->A[i][j].e = 1 + HLCS(l, i+1, j+1);  //recursive case
  } else { // no match
     if(i == t->s1len -1  && j == t->s2len-1) //base case
       t->A[i][j].e = 0;
     else if(i == t->s1len -1) //match later ? (recursive)
       t->A[i][j].e = HLCS(l, i, j+1);  //only j can advance
     else if(j == t->s2len -1)
       t->A[i][j].e = HLCS(l, i+1, j); //only i can advance
     else // take max since both i and j can advance.
       t->A[i][j].e = max(HLCS(l, i+1, j), HLCS(l, i, j+1));
  }
  return t->A[i][j].e;
}

//return memory used in construction.
my_size_t HMemUsed(LCS*l){
  LCSHybrid* t = (LCSHybrid*)l;
  return t->memused;
}

//free all memory allocated in the constructor.
void HDestroy(LCS *l){
  LCSHybrid * t = (LCSHybrid*)l;
  if(t){
    my_size_t i;
    for(i = 0; i < t->s1len; i++)
      FREE(t->A[i]);
    FREE(t->A);
    FREE(t);
  }
}

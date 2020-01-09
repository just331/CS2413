#include <string.h>
#include <stdio.h>
#include "trackedmemory.h"
#include "tabulatedlcs.h"


size_t TLCS(LCS*, size_t, size_t);
size_t TMemUsed(LCS*);
void TDestroy(LCS *);

typedef struct _lcs_table LCSTable;
//opaque table structure
struct _lcs_table{
   LCS li;
   size_t ** A; //pointer to table
   char* s1;  //pointers to each string
   char* s2;
   size_t s1len;  //lengths of strings
   size_t s2len;
   size_t memused;
};


/* Returns An LCS object implemented as a lookup table.
 * Implements LCS interface. 
 * Everything Needed To Compute A Solution
 */
LCS * tabulatedlcs(char * f1, char * f2){
   size_t mem_before = getMemoryUsage();
   LCSTable * t = (LCSTable*)MALLOC(sizeof(LCSTable));
   t->li.lcs = TLCS;
   t->li.memoryusage = TMemUsed;
   t->li.destroy = TDestroy;
   t->s1 = f1;
   t->s2 = f2;
   t->s1len = strlen(f1);
   t->s2len = strlen(f2);
   //printf("Calculating Table... %lu %lu\n", t->s1len, t->s2len);

   long i,j;
   
   //Allocate Table Space
   t->A = (size_t**)MALLOC(sizeof(size_t*)*t->s1len);
   for(i = 0; i < t->s1len; i++)
     t->A[i] = (size_t*)MALLOC(sizeof(size_t)*t->s2len);
   //printf("Table Allocated\n");
   //Fill Table
   for(i = t->s1len-1; i >= 0; i--)
    for(j = t->s2len-1; j >= 0; j--){
      if(i == t->s1len-1 || j ==t->s2len-1) //If last row or last column
        if(t->s1[i] == t->s2[j])
          t->A[i][j] =1;  //MATCH at edge of table. 
        else
          t->A[i][j] = 0; //No Match
      else
        if(t->s1[i] == t->s2[j])
          t->A[i][j] = 1+t->A[i+1][j+1]; //MATCH, extend solution
        else
          t->A[i][j] = max(t->A[i][j+1], t->A[i+1][j]);
            //max lcs length from (i,j) to (s1len,s2len)
     }
     
   size_t mem_after = getMemoryUsage();
   t->memused = mem_after - mem_before;
   //Return Table
   //printf("done\n");
   return (LCS*) t;
}


//Lookup the index values in the LCS table. 
size_t TLCS(LCS*l, size_t i, size_t j){
  LCSTable * t = (LCSTable*)l;
  //printf("retrieving %lu %lu\n", i, j);
  return t->A[i][j];
}

//return memory used in construction. 
size_t TMemUsed(LCS*l){
  LCSTable* t = (LCSTable*)l;
  return t->memused;
}

//free all memory allocated in the constructor. 
void TDestroy(LCS *l){
  LCSTable * t = (LCSTable*)l;
  if(t){
    size_t i;
    for(i = 0; i < t->s1len; i++)
      FREE(t->A[i]);
    FREE(t->A);
    FREE(t);
  }
}

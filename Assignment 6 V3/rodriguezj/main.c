#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"loadfile.h"
#include"tabulatedlcs.h"
#include"memoizedlcs.h"
#include"hybridlcs.h"
#include"trackedmemory.h"

char* load(char*);
char* getSolution(LCS*, char*, char *, my_size_t, my_size_t);

int main(int argc, char ** argv){
  //printf("The main function got started\n" );
  int skipped = 0;
  char command[100];
  char file1[100], file2[100];
  my_size_t load_mem_usage, table_mem_usage, memo_mem_usage;
  clock_t start, end, comp_total, sol_total;
  my_size_t i,j,k;
  const char * const pass[] = {"Verbose Memoized LCS",
                               "Tabulated LCS",
                               "Hybrid LCS",
                               "Memoized LCS" };

  while(scanf("%s %s %s", command, file1, file2) > 2){
  //  printf("attempting to load: %s\n", file1);
    // printf("attempting to load: %s\n", file2);
    char* f1 = loadfile(file1);
    char* f2 = loadfile(file2);
    my_size_t f1len = strlen(f1);
    my_size_t f2len = strlen(f2);if(f1len == 0)
      printf("No Content Read From %s\n", file1);
    if(f2len == 0)
      printf("No Content Read From %s\n", file2);
    if(f1len == 0 || f2len == 0)
      continue;
    // printf("Files Loaded %u %u \n", f1len, f2len);
    for(i = 0; i < 4; i++){
      my_size_t before = getMemoryUsage();
      LCS* l;

      if(f1len * f2len > 100000 && i == 0){
         printf("\n *** skipping noisy output on pass %u\n\n", i);
         skipped = 1;
         continue;
      }

      //Precompute LCS
      start = clock();
      if(i == 0){
        // printf("About to enter memoizedlcs\n" );
        l = memoizedlcs(f1, f2, 1);
        // printf("Exited memoizedlcs\n" );
      }
      if (i == 1){
        // printf("About to enter tabulatedlcs\n" );
        l = tabulatedlcs(f1, f2);
      }
      if (i == 2){
        // printf("About to enter hybridlcs\n" );
        l = hybridlcs(f1, f2);
        // printf("I exited HLCS as well\n" );

      }
      if (i == 3){
        l = memoizedlcs(f1, f2, 0);
      }
      end = clock();
      comp_total = (end-start)/(CLOCKS_PER_SEC/1000);

      start = clock();
      char * sol = getSolution(l, f1, f2, f1len, f2len);
      end = clock();
      sol_total = (end-start)/(CLOCKS_PER_SEC/1000);
      if(i == 0+skipped)
        printf("Solution:\n--------------------------------\n%s\n-------------------------------\n", sol);

      my_size_t mem_use = getMemoryUsage()-before;

      printf("\n%s\n", pass[i]);
      printf("Computation Time: %lu ms\n", comp_total);
      printf("Solution Time: %lu ms\n", sol_total);
      printf("String 1 Length: %u\n", f1len);
      printf("String 2 Length: %u\n", f2len);
      printf("Product: %u\n", f1len*f2len);
      printf("Memory Cost: %u \n", mem_use);
      double average = ((double)mem_use)/((double)(f1len*f2len));
      printf("Amortized Memory Cost: %f\n\n\n", average);

      l->destroy(l);
      FREE(sol);
    }
    FREE(f1);
    FREE(f2);
  }
  assertNoMemoryLeaks();
  return 0;
}


char * getSolution(LCS *l, char* s1, char*s2, my_size_t l1, my_size_t l2){
  my_size_t i, j, k, n;
  i = 0;
  j = 0;
  k = 0;
  //printf("Getting Solution\n");
  n = l->lcs(l,0,0);
  char* sol = (char*)MALLOC(sizeof(char)*(n+1));
  while(i < l1 && j < l2 && k < n){
   //printf("solving %u, %u, %u, %u, %u, %u\n",
   //       i, l1, j, l2, k, n);
   if(i == l1-1 && j == l2 -1) // at bottom right corner.
     if(s1[i] == s2[j]){ //match
       sol[k] = s1[i]; //matching character
       i++; k++;
     } else i++; //exits loop
   else if(i == l1-1) //on edge in s1
     if(s1[i] == s2[j]){ //eager match
       sol[k] = s1[i];
       i++; k++; //exits loop
     } else
       j++; //check later j
   else if(j == l2-1) //on edge in s2
     if(s1[i] == s2[j]){ //eager match
       sol[k] = s1[i];
       j++; k++; //exits loop
     } else
       j++; //check later i
   else //interior space

     if(s1[i] == s2[j]){ // eager match
       sol[k] = s1[i];
       i++; j++; k++;
     } else if(l->lcs(l,i,j+1) == l->lcs(l,i,j))
       j++; //prefer to advance j if possible
     else
       //otherwise advance i
       i++;

   //continue loop;
  }
  sol[k]='\0'; //complete cstring
  return sol;
}


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_SIZE 2001

int reclcs(char * A, char * B){
    if(*A == '\0' || *B =='\0') return 0;
    if(*A == *B) return 1+ reclcs(A+1, B+1);
    else {
      int s1 = reclcs(A+1,B);
      int s2 = reclcs(A,B+1);
      if(s1 > s2) return s1;
      else return s2;
    }
}

void clean(char*c){
  if(*c == '\0') return;
  if(*c == '\n')
     *c = '\0';
  else clean(c+1);
}

int main(int argc, char ** argv){
  char l1[LINE_SIZE], l2[LINE_SIZE], 
       temp[LINE_SIZE], best[LINE_SIZE];
  *temp= '\0';
  *best='\0';
  while(fgets(l1, LINE_SIZE, stdin) &&    
        fgets(l2, LINE_SIZE, stdin)){
    clean(l1); clean(l2);
    printf("lcs has length %d\n", reclcs(l1,l2));   
  }
  return 0;
}

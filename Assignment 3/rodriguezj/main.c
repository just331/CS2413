#include "stdheader.h"
#include "sort.h"



int main(int argc, char ** argv){
  int size;
  while(scanf("%d", &size) > 0){
     char sortroutine[21];
     int *array;
     array = (int*)malloc(sizeof(int)*size);
     int i;
     for(i = 0; i < size; i++){
       scanf("%d", array + i);
     }
     scanf("%s", sortroutine);
     
     if(strcmp(sortroutine, "BubbleSort") == 0){
        BubbleSort(array, size);
     }
        
     else if(strcmp(sortroutine, "MergeSort") == 0){
        MergeSort(array,size);
     }
            
     else if(strcmp(sortroutine, "SelectionSort") == 0){
        SelectionSort(array, size);
     }
        
     else {
       printf("Invalid input.\n");
     }
  }
  return 0;
}

#include "stdheader.h"
#include "sort.h"


void Print(int *array, int size){
  int i = 0, *p;
  p = array;
  while (i < size){
    printf("%d ", *p++);
    i++;
  }
  printf("\n");
}

void Swap(int *p, int *q){
  int temp;
  temp = *p;
  *p = *q;
  *q = temp;
}


void BubbleSort(int *array, int size){
    int *sorted, *p, *q, i = 0, j;
    Print(array, size);
    while(i < size){
      p = array + i;
      j = i + 1;
      while( j < size){
        q = array + j;
        if(*q < *p)
          Swap(p, q);
        q++;
        j++;
      }
      Print(array, size);
      i++;
    }
}


void SelectionSort(int *array, int size){
  int *sorted; 
  int *max; 
  int *t;
  int i;
  int j;
  i = 0;

  while(i < size){

    sorted = array + (size - i);
    max = sorted;
    t = max - 1;
    j = 1 + i;

    while(j <= size){

      if(*t > *max)
        max = t;
      t--;
      j++;
    }

    if(*max != *sorted)
      Swap(max, sorted);
    i++;
    Print(array, size);
  }

}

int * MergeSort(int * array, int size){

  int *printer;
  int i = 0;

  printer = array;


  while(i++ < size){
    printf("%d ",*printer++ );
  }
  printf("\n" );

  if(size < 2){
    i = 0;
    printer = array;
    while(i++ < size){
      printf("%d ",*printer++ );
    }
    printf("\n" );
    return array;
  }
  else{
    int *leftH; 
    int *rightH;
    int *sortedArray; 
    int leftSize; 
    int rightSize;
    leftH = array;
    leftSize = size/2;
    rightSize = size - leftSize;
    rightH = array + leftSize;
    sortedArray = (int *)malloc(size * sizeof(int));
    sortedArray = merge( MergeSort(rightH, rightSize), MergeSort(leftH, leftSize), leftSize, rightSize, sortedArray);
    return sortedArray;
  }

}

int * merge(int *right, int *left, int leftLen, int  rightLen, int *array){
  int  i = 0; 
  int j = 0; 
  int k = 0;
  int size; 
  int *sortedArray;
  size = leftLen + rightLen;
  sortedArray = array;

  while((i < leftLen) && (j < rightLen) ) {
    if (*left <= *right){
      *sortedArray = *left++;
      i++;
    }
    else{
      *sortedArray = *right++;
      j++;
    }
    sortedArray++;
  }

  while (i < leftLen) {
    *sortedArray++ = *left++;
    i++;
  }

  while (j < rightLen) {
    *sortedArray++ = *right++;
    j++;
  }

  sortedArray = array;

  for(i = 0; i < size ; i++){
    printf("%d ", *sortedArray++);
  }
  printf("\n" );

  return array;

}

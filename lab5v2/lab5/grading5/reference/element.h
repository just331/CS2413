#ifndef ___Element_DEFINITION_HEADER_
#define ___Element_DEFINITION_HEADER_

#include<string.h>
#include<stdio.h>

/************************************
*******
******* Definition Of Element, 
******* Change this file's definition of Element
******* To Change Any Data Structure Which Takes
******* Elements As Content. 
*******
*************************************/

struct _box{
   size_t H, W, D;
   char O[21];
};

typedef struct _box Element;


/*eCompare: Element x Element -> {-1, 0, 1}
* This function is not defined here.  
* Compare two Elements. 
* return -1 if the left Element is less than
* return 1 if the left Element is larger than
* return 0 if they are equal or are a match.  
*/ 
static int eCompare(Element left, Element right){
  size_t leftVolume = left.H * left.W* left.D;
  size_t rightVolume = right.H * right.W * right.D;
  if( leftVolume > rightVolume) return 1;
  if( leftVolume < rightVolume) return -1;
  return 0;
}

/* printElement
* This is a fold-ready function. 
* a is not used, can be anything, 
* returns a. 
*/
static void * printElement(void *a, Element e){
  printf("Box(H = %lu, W = %lu, D = %lu, O = %s)\n",
         e.H, e.W, e.D, e.O);
  return a;
}






#endif

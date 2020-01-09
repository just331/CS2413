#ifndef ___map__h___
#define ___map__h___

#include<stdlib.h>
#include<stdio.h>
#include"my_size_t.h"

//KEY  DEFINITION
typedef struct _key Key;
struct _key{
  my_size_t i;
  my_size_t j;
};

/********
*** About This Key Definition
***
*** When used for memoization,
*** the keys need to contain
*** all the relevant input to a function
***
*** In this case the input is two indexes
*** into the strings we are looking for
*** the lcs of.
***
************/

//KEY COMPARE:  0 when equal, -1 when not equal
static int keyCompare(Key left, Key right){
  if(left.i == right.i && left.j == right.j)
    return 0;
  return -1;
}

//printKey
static void printKey(Key k, char* location, my_size_t n){
  snprintf(location, n, "(%u, %u)", k.i, k.j);
}

//VALUE DEFINITION
typedef my_size_t Value;


/********
*** About This Value Definition
***
*** When used for memoization,
*** the value needs to contain
*** all the relevant output of a function.
***
*** In this case the output is the my_size_t
*** length of the lcs starting from the
*** two string indexes in the key.
***
************/

//printValue
static void printValue(Value v, char* location, my_size_t n){
  snprintf(location, n, "%u", v);
}


/*
* Map Interface
*
* If key does not exist, pointer in Value ** is set to null
* Otherwise the value is written to the space pointed to.
*/
typedef struct _map_interface Map;
struct _map_interface{
  Map* (*add)(Map*, Key, Value);
  Map* (*remove)(Map*, Key);
  Map* (*lookup)(Map*, Key, Value**);
  void (*destroy)(Map*);
};





#endif

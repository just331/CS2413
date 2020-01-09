#ifndef ___lcs_h___
#define ___lcs_h___

#include"my_size_t.h"

typedef struct _lcs LCS;
struct _lcs{
  my_size_t (*lcs)(LCS*, my_size_t, my_size_t);
  my_size_t (*memoryusage)(LCS*);
  void (*destroy)(LCS*);
};



static inline my_size_t max(my_size_t a, my_size_t b)
  {if(a>b)return a;return b;}
#endif

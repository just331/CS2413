#ifndef ___lcs_h___
#define ___lcs_h___

typedef struct _lcs LCS;
struct _lcs{
  size_t (*lcs)(LCS*, size_t, size_t);
  size_t (*memoryusage)(LCS*);
  void (*destroy)(LCS*);
};



static inline size_t max(size_t a, size_t b)
  {if(a>b)return a;return b;}
#endif

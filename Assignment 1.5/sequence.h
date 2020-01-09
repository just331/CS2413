// Justin Rodriguez
// CS 2413
// Wertz 
// 9-8-16

#ifndef ___SEQUENCE__HEADER____
#define ___SEQUENCE__HEADER____
#include "stdheader.h"
//#include "trackedmemory.h"


struct _token{
  char text[21];  
};

typedef struct _token token;



struct _seq_interface{
    token (*getCurrent)(struct _seq_interface*);
    void (*gotoNext)(struct _seq_interface*);
    void (*destroy) (struct _seq_interface*);
};
typedef struct _seq_interface seq;




struct _fib_seq{
  seq si;  
  int next; 
  int current; 
};

typedef struct _fib_seq fib;


struct _Foxsays_seq{
    seq si;
    token A;
    token B;
    int index;
    
};

typedef struct _Foxsays_seq foxsays;

struct _Rot_seq{
    seq si;
    int next;
    int current;
    int array[9];
    int index;
    int A;
    int B;

};

typedef struct _Rot_seq rot;



struct _sieve_seq{
  seq si;
  int * pArray; 
  int aSize;    
  int last;     
};
typedef struct _sieve_seq sieve;



seq * newSieveSeq(int A);
seq * newRotSeq(int A, int B);
seq * newFoxSaysSeq(token A, token B);
seq * newFibSeq(int A, int B);

#endif

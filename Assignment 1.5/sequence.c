// Justin Rodriguez
// CS 2413
// Wertz 
// 9-8-16

#include "stdheader.h"
#include "sequence.h"
//#include "trackedmemory.h"


//Fib Sequence Implementation 


void fibGotoNext(seq * sthis){
  fib* this = (fib*) sthis;
  int prev = this->current;
  this->current = this->next;
  this->next = prev + this->current;
}


token fibGetCurrent(seq * sthis){
  fib* this = (fib*) sthis;
  token t;
  //translate integer to string and package in token
  snprintf(t.text, sizeof(token)-1, "%d",this->current);   
  return t; //not a pointer, safe to return;
  
}

void fibDestroy(seq* sthis){
  free(sthis); //return memory occupied by instance back to system.
}

//Fib Constructor
seq * newFibSeq(int A, int B){
  //allocate space for instance
  fib * f = (fib*) malloc(sizeof(fib));
  //format  interface with instance related functions. 
  f->si.getCurrent = fibGetCurrent;
  f->si.gotoNext = fibGotoNext;
  f->si.destroy = fibDestroy;
  //format private variables of instance.
  f->next = B;
  f->current = A;
  //return instance as pointer to its interface.
  return (seq*) f;
}


//FoxSays Sequence implementation


void foxGotoNext(seq* s){
    foxsays* fseq = (foxsays*)s;
    fseq -> index++;
}

token foxGetCurrent(seq *s){
    foxsays* fseq = (foxsays*)s;
    if(fseq -> index == 0){
        return fseq -> A;
    }
    else if(fseq -> index % 6 == 0){
        return fseq -> B;
    }
    else{
        return fseq -> A;
    }
}


void foxDestroy(seq * s){
    free(s);    
}

seq * newFoxSaysSeq(token tA, token tB){
    foxsays *fox = (foxsays*)(malloc(sizeof(foxsays)));
    fox -> si.getCurrent = foxGetCurrent;
    fox -> si.gotoNext = foxGotoNext;
    fox -> si.destroy = foxDestroy;
    fox -> A = tA;
    fox -> B = tB;
    fox -> index = 0;
    return (seq*) fox;
    
}



// Rotation Sequence Implementation


token rotGetCurrent(seq * sthis){
  rot* this = (rot*) sthis;
  token t;
  snprintf(t.text, sizeof(token)-1, "%d",this->current);   
  return t; 
}

void rotDestroy(seq* s){
    rot* r = (rot*)s;
    free(r);
}


void rotGotoNext(seq* s){
    rot* r = (rot*)s;
    r -> index++;
    r -> current = r -> array[r -> index % 8];
    return;
    
}

seq * newRotSeq(int A, int B){
    rot *r = (rot*)malloc(sizeof(rot));
    r -> si.getCurrent = rotGetCurrent;
    r -> si.gotoNext = rotGotoNext;
    r -> si.destroy = rotDestroy;
    r -> current = A;
    r -> array[0] = A;
    r -> array[1] = A + B;
    r -> array[2] = B;
    r -> array[3] = 0;
    r -> array[4] = A * -1;
    r -> array[5] = A * -1 + B * -1;
    r -> array[6] = B * -1;
    r -> array[7] = 0;
    r -> index = 0;
    
    return (seq*)r;
}


//Sieve Sequence Implementation


token sieveGetCurrent();
void sieveGotoNext();
void sieveDestroy();

//sieve constructor
seq * newSieveSeq(int P){
  //allocate space for instance
  sieve * s = (sieve *) malloc(sizeof(sieve));
  //format  interface with instance related functions. 
  s->si.getCurrent = sieveGetCurrent;
  s->si.gotoNext = sieveGotoNext;
  s->si.destroy = sieveDestroy;
  //format private variables of instance.
  s->aSize = 2; //initial array size
  s->pArray = (int*) malloc(sizeof(int)*s->aSize);  //get space 
  s->pArray[0] = P; //set the seed prime.
  s->last = 0;  //index of seed prime, the last prime. 
  //return pointer to instance interface. 
  return (seq*) s;
}



//gotoNext function for sieve instance
void sieveGotoNext(seq * sthis){
  sieve* this = (sieve*) sthis;
  if(this->last == this->aSize-1) { // resize array condition
    int newSize = this->aSize * 2; //double in size
    int * newArray = (int *) malloc(sizeof(int)*newSize); //space for new array
    memcpy(newArray, this->pArray, sizeof(int)*this->aSize); //copy content 
    free(this->pArray); //free old array
    this->pArray = newArray;  //set new array
    this->aSize = newSize;  //set size of new array
  }
  int candidate = this->pArray[this->last]+1; //next number after last saved "prime"
  while(1){
    int i;
    for(i = 0; i <= this->last; i++){
      if((candidate % this->pArray[i]) == 0){
        break; //candidate divisible by ith prime, break for loop.  
      }
    }
    //(if i > last) the candidate survives the for loop, it is prime. 
    if(i > this->last){
      this->last++;
      this->pArray[this->last] = candidate; //add successful candidate to array
      break;
    } else {
      //go to next candidate because for loop was broken. 
      candidate++;
    }
  } 
}
  
 
//getCurrent function for sieve instance
token sieveGetCurrent(seq * sthis){
  sieve * this = (sieve *) sthis;
  token t;
  snprintf(t.text,sizeof(token)-1, "%d", this->pArray[this->last]); //turn int into token
  return t;
}

//destroy function for sieve instance (destructor)
void sieveDestroy(seq* sthis){
  sieve * this = (sieve *) sthis;
  //constructor allocated array for primes, need to free it. 
  free(this->pArray);
  free(this); //return memory occupied by instance back to system.
}


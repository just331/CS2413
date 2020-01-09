#include "hashmap.h"
#include "trackedmemory.h"
#include "map.h"

#define NEVER_OCCUPIED 0
#define OCCUPIED 1
#define PREV_OCCUPIED 2


Map * HMadd (Map*, Key, Value);
Map * HMremove(Map*, Key);
Map * HMlookup(Map*, Key, Value**);
void HMdestroy(Map*);

typedef struct _oa_entry entry;
struct _oa_entry{
  Key k;
  Value v;
  char state;
};


typedef struct _hash_map HMap;
struct _hash_map{
  Map mi;
  entry * T;
  size_t * primes;
  size_t pts;
  size_t ts;
  size_t ne;
  size_t p1;
  size_t p2;
  double load; 
  char flag;
  primes = (size_t *)MALLOC(sizeof(size_t)*20);
  primes[0] = 37;
  primes[1] = 101;
  primes[2] = 307;
  primes[3] = 1019;
  primes[4] = 2011;
  primes[5] = 4201;
  primes[6] = 8999;
  primes[7] = 20051;
  primes[8] = 40039;
  primes[9] = 80021;
  primes[10] = 160001;
  primes[11] = 320057;
  primes[12] = 640009;
  primes[13] = 1280023;
  primes[14] = 2800001;
  primes[15] = 5600027;
  primes[16] = 11200001;
  primes[17] = 22400009;
  primes[18] = 32452843;
  primes[19] = 43489877;
  pts = 0;
  ts = primes[pts];
  
};

Map * newHashMap(char flag, size_t ts){
   HMap * m = (HMap*)MALLOC(sizeof(HMap));
   m -> ne =0;
   m -> T = (entry*)CALLOC(sizeof(entry)* h -> ts);
   m -> p1 = 29;
   m -> p2 = 17
   m -> load = .7
   return (Map*)m;
}

Map * HMadd (Map*m, Key k, Value v){
  HMap * hm = (HMap*)m;
  resize(hm); //make sure there is room in the table.
  size_t start = hash(&k, sizeof(Key), hm -> p1, hm -> ts);
  char keyText[21], valueText[21];
  printKey(k, keyText, 21);
  printValue(v, valueText, 21);
  if(flag)
    printf("adding %s %s at %lu\n", keyText, valueText, start);
  
  return m;
}

Map * HMremove(Map*m, Key k){
  HMap * hm = (HMap*)m;
  if(m == NULL) return m;
  size_t p = hash(&k, sizeof(key), m -> p. m -> ts);
  if(m -> T[p] == NULL) return m;
  if(keycompare(k, m ->T[p] -> entry -> k ) == 0){
    entry* temp = m -> T[p];
    m -> T[p] = temp -> next;
    free(temp);
    return m;
  }
  entry * temp = m -> T[p];
  while(temp -> next){
    if(keycompare(k, temp -> next -> entry -> k) == 0){
      entry* temp2 = temp -> next;
      temp -> next = temp2 -> next;
      free(temp2);
      return m;
    }
    temp = temp -> next;
  }
  return m;
}

Map * HMlookup(Map* m, Key k, Value** v){
  char keyText[21];
  printKey(k, keyText, 21);
  size_t start = hash(&k, sizeof(key), hm -> p1, hm -> ts);
  
  
  
  
  
  if(flag &&  *v){
    char valueText[21];
    printValue(**v, valueText, 21);
    printf("lookup %s at %lu found %s\n", keyText, start, valueText);
  }
  else{
    printf("lookup %s at %lu undefined\n", keyText)
  }
  return m;
}

void HMdestroy(Map*m){
  
}


void resize(HMap*hm){
  if(hm == NULL)return;
  if( (hm -> ne / hm -> ts) >= hm -> load){
    size_t newsize = (h -> ts)*2;
    entry* newtable = (entry*)CALLOC(sizeof(entry)*newsize);
    size_t i;
    for(i = 0; i <= hm -> ts; i++){
      while(hm -> T[i]){
        entry* temp = hm -> T[i];
        hm -> T[i] = temp -> next;
        temp -> next = NULL;
        size_t p = Hash(&(temp -> entry -> k), sizeof(Key), hm -> p, newsize );
        temp -> next = newtable[p];
        newtable[p]; = temp;
      }
    }
  }
  free(hm -> T);
  hm -> T = newtable;
  hm -> ts = newsize;
}













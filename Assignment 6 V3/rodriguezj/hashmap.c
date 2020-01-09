#include"hashmap.h"
#include"trackedmemory.h"

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
  my_size_t * primes;
  my_size_t pts;
  my_size_t ts;
  my_size_t ne;
  my_size_t p1;
  my_size_t p2;
  double load;
  char flag;
};

void resizeAdd(Key k, Value v, entry*T, HMap *hm);

my_size_t hash(void * d, my_size_t n, my_size_t p, my_size_t ts){
  my_size_t a = 0,i = 0;
  unsigned char * e = (char*)d;
  while(i < n){
    a = a*p + e[i];
    i++;
  }
  return a % ts;
}

Map * newHashMap(char flag){
   HMap * m = (HMap*)MALLOC(sizeof(HMap));
   m->mi.add = HMadd;
   m->mi.remove = HMremove;
   m->mi.lookup = HMlookup;
   m->mi.destroy = HMdestroy;
   m->primes = (my_size_t *)MALLOC(sizeof(my_size_t)*20);
   m->primes[0] = 37;
   m->primes[1] = 101;
   m->primes[2] = 307;
   m->primes[3] = 1019;
   m->primes[4] = 2011;
   m->primes[5] = 4201;
   m->primes[6] = 8999;
   m->primes[7] = 20051;
   m->primes[8] = 40039;
   m->primes[9] = 80021;
   m->primes[10] = 160001;
   m->primes[11] = 320057;
   m->primes[12] = 640009;
   m->primes[13] = 1280023;
   m->primes[14] = 2800001;
   m->primes[15] = 5600027;
   m->primes[16] = 11200001;
   m->primes[17] = 22400009;
   m->primes[18] = 32452843;
   m->primes[19] = 43489877;
   m->pts = 0;
   m->ts = m->primes[m->pts];
   m->ne = 0;
   m->T = (entry*)CALLOC(sizeof(entry), m->ts);
   m->p1 = 29;
   m->p2 = 17;
   m->load = 0.7;
   m->flag = flag;
   return (Map*)m;
}

void resize(HMap*);

Map * HMadd (Map*m, Key k, Value v){
  HMap *hm = (HMap*)m;
  resize(hm);
  my_size_t start, offset, index;
  char keyText[21], valueText[21];
  printKey(k, keyText, 21);
  printValue(v, valueText, 21);
  start = hash(&k, sizeof(Key), hm->p1, hm->ts);

  if(hm->flag)
  printf("adding %s %s at %u\n", keyText, valueText, start);

  offset = hash(&k, sizeof(Key), hm->p2, hm->ts);

  index = (start % hm->ts);
  if(!offset)
    offset += hm->p2;


  while(hm->T[index].state == OCCUPIED)
    index = ((index + offset)%hm->ts);

  hm->T[index].k = k;
  hm->T[index].v = v;
  hm->T[index].state = OCCUPIED;

  hm->ne += 1;

  return m;
}

Map * HMremove(Map*m, Key k){
  return m;
}

Map * HMlookup(Map* m, Key k, Value** v){
  HMap *hm = (HMap *)m;
  my_size_t start, offset, index;
  char keyText[21];
  printKey(k, keyText, 21);

  start = hash(&k, sizeof(Key), hm->p1, hm->ts);
  offset = hash(&k, sizeof(Key), hm->p2, hm->ts);
  index = (start % hm->ts);

  if(!offset)
    offset += hm->p2;

  while((keyCompare(hm->T[index].k, k) != 0) && (hm->T[index].state != NEVER_OCCUPIED))
    index = ((index+offset) % hm->ts);

  if(hm->T[index].state == NEVER_OCCUPIED)
    *v = NULL;
  else
    **v = hm->T[index].v;

  if(hm->flag && *v){
    char valueText[21];
    printValue(**v, valueText, 21);
    printf("lookup %s at %u found %s\n", keyText, start, valueText);
  }

  else if(hm->flag)
    printf("lookup %s at %u undefined\n", keyText, start);


  return m;
}

void HMdestroy(Map*m){
  HMap * hm = (HMap*)m;
  FREE(hm->T);
  FREE(hm->primes);
  FREE(hm);
}

void resizeAdd(Key k, Value v, entry *T, HMap *hm){
    my_size_t start, offset, index;

    start = hash(&k, sizeof(Key), hm->p1, hm->ts);
    offset = hash(&k, sizeof(Key), hm->p2, hm->ts);


    index = (start % hm->ts);
    if(!offset)
      offset += hm->p2;

    while(T[index].state == OCCUPIED)
      index = ((index + offset) % hm->ts);

    T[index].k = k;
    T[index].v = v;
    T[index].state = OCCUPIED;

    return;
}


void resize(HMap*hm){
  double f = (double) hm->ne / (float) hm->ts;
  if(f >= 0.7){
    my_size_t oldTS, i;
    Key k;
    Value v;
    oldTS = hm->ts;
    entry * T = (entry*)CALLOC(sizeof(entry), hm->ts);
    entry * oldTable;
    i = 0;
    hm->ts = hm->primes[++hm->pts];
    T = (entry*)CALLOC(sizeof(entry), hm->ts);
    while(i < oldTS){
      if(hm->T[i].state == OCCUPIED){
        k = hm->T[i].k;
        v = hm->T[i].v;
        resizeAdd(k, v, T, hm);
      }

      i++;
    }
    oldTable = hm->T;
    hm->T = T;
    FREE(oldTable);

  }

  return;


}

#ifndef __MULTISET_INTERFACE_H__
#define __MULTISET_INTERFACE_H__
#include"element.h"

typedef struct _multiset_interface MultiSet;
struct _multiset_interface{
  MultiSet * (*add)(MultiSet*, Element);
  MultiSet * (*remove)(MultiSet*, Element);
  MultiSet * (*removeAll)(MultiSet*, Element);
  int (*contains)(MultiSet *, Element);
  size_t (*count)(MultiSet *, Element);
  void (*destroy)(MultiSet *);
};

#endif

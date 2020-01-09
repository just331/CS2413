#ifndef ___GRAPH_HEADER__
#define ___GRAPH_HEADER__

#include "stdheader.h"

typedef struct _edata edata;
struct _edata{
    int start;
    int end;
    int cost;
};


typedef struct _edge edge;
struct _edge{
    char from[4];
    char to[4];
    edata d;
    edge* next;
};

typedef struct _vdata vdata;
struct _vdata{
    char APC[4];
};


typedef struct _vertex vertex;
struct _vertex{
    vertex *next;
    vdata vdatav;
    
};

typedef struct _Graph Graph;
struct _Graph{
    vertex* vhead;
    edge* ehead;
};


Graph* createGraph();
int edgecmp(edge*, edge*);
void addEdge(Graph*, edge*);
edge* newEdge(Graph*, edata*, vertex, vertex);
void addVertex(Graph*, vertex*);
vertex* newVertex(Graph*, vdata);
vertex* getVertex(Graph*, char[]);
void ListAll(Graph*);
//void printVertices(Graph*);
void ListAPC(Graph*, char[]);


#endif
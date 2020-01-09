#include "stdheader.h"
#include "graph.h"

int main(int argc, char** argv){
    char command[100];
    Graph* g = createGraph();
    
    while(scanf("%s", command) > 0){
        //printf("command is: %s\n", command);
        if(strcmp(command, "Flight") == 0){
           // printf("here in flight\n");
            char apc1[4];
            char apc2[4];
            int s;
            int e;
            int c;
            scanf("%s", apc1);
            scanf("%s", apc2);
            scanf("%d", &s);
            scanf("%d", &e);
            scanf("%d", &c);
            vertex* t1;
            vertex* t2;
            t1 = getVertex(g, apc1);
            t2 = getVertex(g, apc2);
            vdata data1;
            vdata data2;
            vertex* v1;
            vertex* v2;
            if(t1 == NULL){
                strcpy(data1.APC, apc1);
                v1 = newVertex(g, data1);
                addVertex(g, v1);
            }
            if(t2 == NULL){
                strcpy(data2.APC, apc2);
                v2 = newVertex(g, data2);
                addVertex(g, v2);
            }
          //  printVertices(g);
            edata edata1;
            edata1.start = s;
            edata1.end = e;
            edata1.cost = c;
            edge* e1 = newEdge(g, &edata1, *v1, *v2 );
            addEdge(g, e1);
           // printf("Flight created\n");
        }
        else if(strcmp(command, "List") == 0){
          //  printf("here\n");   
            char apc[4];
            
            memset(apc, 0, 4);
            scanf("%s", apc);
            if(strcmp(apc, "*") == 0){
                ListAll(g);
            }
            else{
                ListAPC(g, apc);    
            }
            
        }

        else{
            printf("%s is not a valid command.", command);
        }
    } 
    return 0;
} 
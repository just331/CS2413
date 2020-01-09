#include "stdheader.h"
#include "graph.h"

Graph * createGraph(){
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g -> vhead = NULL;
    g -> ehead = NULL;
    
    return g;
}


int edgecmp(edge* e1, edge* e2){
    if(e1 == NULL && e2 == NULL)
        return 0;
    else if(e1 != NULL && e2 == NULL)
        return -1;
    else{
        if(strcmp(e1 -> from, e2 -> from) < 0)
            return -1;
        else if(strcmp(e1 -> from, e2 -> from) > 0)
            return 1;
        else{
            if(strcmp(e1 -> to, e2 -> to) < 0)
                return -1;
            else if(strcmp(e1 -> to, e2 -> to) > 0)
                return 1;
            else{
                if(e1 -> d.start < e2 -> d.start)
                    return -1;
                else if(e1 -> d.start > e2 -> d.start)
                    return 1;
                else{
                    if(e1 -> d.end < e2 -> d.end)
                        return -1;
                    else if(e1 -> d.end > e2 -> d.end)
                        return 1;
                    else{
                        if( e1 -> d.cost < e2 -> d.cost)
                            return -1;
                        else if( e1 -> d.cost < e2 -> d.cost)
                            return 1;
                        else{
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

void addEdge(Graph* g, edge* e){
    //printf("Entered add edge\n");
    if( g -> ehead == NULL)
        g -> ehead = e;
    else{
        edge* temp = g -> ehead;
        if(edgecmp(e, temp) < 0){
            e -> next = temp;
            g -> ehead = e;
        }
        else{
            while(edgecmp(e, temp -> next) > 0){
                temp = temp -> next;
            }
            e -> next = temp -> next;
            temp -> next = e;
        }
    }
    //printf("Exiting add edge\n");
}

edge* newEdge(Graph* g, edata* data, vertex v1, vertex v2){
    edge* newEdge = (edge*)malloc(sizeof(edge));
    strcpy(newEdge ->from, v1.vdatav.APC);
    strcpy(newEdge ->to, v2.vdatav.APC);
    newEdge -> d = *data;
    return newEdge;
    
}

/*void printVertices(Graph * g){
    vertex* temp = g->vhead;
    while(temp!=NULL){
      //  printf("%s->",temp->vdatav.APC);
        temp = temp->next;
    }
    printf("\n");
}*/


void addVertex(Graph*g, vertex* v1){
    //printf("in addVerte\n");
    if(g -> vhead == NULL){
        g -> vhead = v1;
    }
    else{
        vertex* temp;
        temp = g-> vhead;

        //Adding at head
        if(strcmp(v1 -> vdatav.APC, temp -> vdatav.APC) < 0){
            v1 -> next = temp;
            g -> vhead = v1;
        }
        //Checking each node after head
        else{
            while(temp -> next != NULL){
                if(strcmp(v1 -> vdatav.APC, temp -> next -> vdatav.APC) < 0)
                    break;
    //            printf("temp: %s\n", temp->vdatav.APC);
                temp = temp -> next;
            }
            v1 -> next = temp -> next;
            temp -> next = v1;
        }
    }
   // printf("exit addVertex\n");
}


vertex* newVertex(Graph* g, vdata j){
    vertex* v = (vertex*)malloc(sizeof(vertex));
    v -> next = NULL;
    v -> vdatav = j;
    return v;
}



vertex* getVertex(Graph* g, char apc[]){
        //printf("in getVertex\n");
        vertex* temp;
        temp = g -> vhead;
        while(temp!= NULL){
            if(strcmp(temp -> vdatav.APC, apc) == 0){
       //          printf("out of getVertex, found\n");
                return temp;
            }
            temp = temp -> next;
            
        }
     //   printf("out of getVertex\n");
        return NULL;

}


// Incorrectly printing APC w/ wrong flights or no flights at all
void ListAll(Graph*g){
    edge* temp;
    temp = g -> ehead;
    vertex* vtemp = g -> vhead;
    //char currentAPC[4];
    if(temp == NULL){
        printf("Network Is Empty\n");
        return;
    }
    //strcpy(currentAPC, temp -> from);

    printf("Flights From %s\n", vtemp -> vdatav.APC); // check for NULL
    
    while(temp != NULL){
        if(strcmp(vtemp -> vdatav.APC, temp -> from) !=0){
            printf("-- No Flights\n");
            vtemp = vtemp -> next;
            printf("Flights From %s\n", vtemp -> vdatav.APC);
            
            //strcpy(currentAPC, temp -> from);
        }
        else{
            printf("-- Flight to %s start:%d end:%d cost:%d\n", temp -> to, temp -> d.start, temp -> d.end, temp -> d.cost);
            temp = temp -> next;
            if(temp == NULL){
                vtemp = vtemp -> next;
                break;
                
            }
            
            else if(strcmp(vtemp -> vdatav.APC,temp -> from) != 0){
                vtemp = vtemp -> next;
                printf("Flights From %s\n", vtemp -> vdatav.APC);
            }    

            
            
        }
        
    }
    while(vtemp != NULL){
                    printf("Flights From %s\n", vtemp -> vdatav.APC);
                    printf("-- No Flights\n");
                    vtemp = vtemp -> next;
    }
   // printf("exiting ListAll\n");
}

void ListAPC(Graph*g, char apc[]){
    edge* temp = g -> ehead;
    vertex* vtemp = getVertex(g, apc);
    if(vtemp == NULL){
        printf("Airport %s Not Found\n", apc);
        return;
    }
    else{
        int found = 0;
        printf("Flight From %s\n", apc);
        while(temp !=NULL){
            if(strcmp(temp -> from, apc) == 0){
                found = 1;
                printf("-- Flight To %s start:%d end:%d cost:%d\n", temp -> to, temp -> d.start, temp -> d.end, temp -> d.cost);
                temp = temp -> next;
            }
        
            temp = temp -> next;
        }
        if(found == 0){
            printf("-- No Flights\n");
        }    
    }

}

















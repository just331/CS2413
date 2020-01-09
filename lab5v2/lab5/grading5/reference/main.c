#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"element.h"
#include"avltree.h"
#include"multisetbstree.h"
#include"trackedmemory.h"

int main(int argc, char ** argv){

  Element e;
  char command[100];
  
  BSTree * b = newAVLTree();
  MultiSet * m = newBSTMultiSet(b);
  
  while(scanf("%s", command) > 0){
    
    if(strcmp(command, "Add") == 0){
       scanf("%lu %lu %lu %s", &e.H, &e.W, &e.D, e.O);
       m->add(m, e);
    } else if(strcmp(command, "Remove") == 0){
       scanf("%lu", &e.H);
       e.W = 1;
       e.D = 1;
       m->remove(m, e);
      
    } else if(strcmp(command, "RemoveAll") == 0){
       scanf("%lu", &e.H);
       e.W = 1;
       e.D = 1;
       m->removeAll(m, e);
    } else if(strcmp(command, "Count") == 0){
       scanf("%lu", &e.H);
       e.W = 1;
       e.D = 1;
       printf("There are %lu boxes with volume %lu.\n", 
              m->count(m,e), e.H);
    } else if(strcmp(command, "Inorder") == 0){
       printf("Inorder:\n");
       b->inorder(b, NULL, printElement);
    } else if(strcmp(command, "Preorder") == 0){
       printf("Preorder:\n");
       b->preorder(b, NULL, printElement);
    } else if(strcmp(command, "Postorder") == 0){
       printf("Postorder:\n");
       b->postorder(b, NULL, printElement);
    } else {
       printf("unrecognized command: %s\n", command);
    } 
  }
  m->destroy(m);
  b->destroy(b);
  assertNoMemoryLeaks();
  return 0;
}

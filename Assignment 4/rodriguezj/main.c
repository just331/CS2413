#include "BST.h"

int main(int argc, char ** argv){
    char command[100];
    BSTree* t = newBSTree();

    while(scanf("%s", command) > 0){
        if(strcmp(command, "insert") == 0){
            char first[21];
            char last[21];
            scanf("%s", first);
            scanf("%s", last);
            Element e;
            strcpy(e.first, first);
            strcpy(e.last, last);
            t->insert(t,e);
        }
        
        else if(strcmp(command, "inorder") == 0){
             printf("Inorder:\n");
            t -> inorder(t);
        }
        else if(strcmp(command, "preorder") == 0){
            printf("Preorder:\n");
            t -> preorder(t);
        }
        else if(strcmp(command, "postorder") == 0){
            printf("Postorder:\n");
            t -> postorder(t);
        }
        if(strcmp(command, "remove") == 0){
            int i = 0;
            char first[21];
            char last[21];
            scanf("%s", last);
            scanf("%s", first);
            Element e;
            strcpy(e.last, last);
            if(strcmp(first, "*") == 0){
                t -> root = recRemoveAll(t -> root, last, &i);
            }
            else{
                strcpy(e.first, first);
                 t -> root = t -> remove(t -> root, e, &i);
            }
           
        }
        else if(strcmp(command, "list") == 0 ){
            char name[21];
            scanf("%s", name);
            printf("Listing %s:\n", name);
            ListLast(t -> root, name);
            
        }
        
    }
    return 0;
}
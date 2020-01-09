#include "AVL.h"

int main(int argc, char ** argv){
    char command[100];
    AVL* t = newAVL();
    
    while(scanf("%s", command) > 0){
        if(strcmp(command, "Add") == 0){
            int H;
            int W;
            int D;
            char O[21];
            scanf("%d", &H);
            scanf("%d", &W);
            scanf("%d", &D);
            scanf("%s", O);
            Element e;
            e.H = H;
            e.W = W;
            e.D = D;
            e.V = e.H * e.W * e.D;
            strcpy(e.O, O);
            t->root = add(t->root,e);
        }
        
        else if(strcmp(command, "Inorder") == 0){
            printf("Inorder:\n");
            inorder(t);
        }
        else if(strcmp(command, "Preorder") == 0){
            printf("Preorder:\n");
            preorder(t);
        }
        else if(strcmp(command, "Postorder") == 0){
            printf("Postorder:\n");
            postorder(t);
        }
        else if(strcmp(command, "Remove") == 0){
            bool del = false;
            int V;
            scanf("%d", &V);
            removeNode(t -> root, V, &del);
           
        }
        else if(strcmp(command, "RemoveAll") == 0 ){
            int V;
            scanf("%d", &V);
            removeAll(t, V);
            
        }
        else if(strcmp(command, "Count") == 0 ){
            int V;
            scanf("%d", &V);
            int c = count(t -> root, V);
            printf("There are %d boxes with volume of %d.\n", c, V);
            
        }
        
    }
    return 0;
}
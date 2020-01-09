#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"


int main(int argc, char **argv){

  char command[30];
  char path[1001];
  md m;
  m.root = newFileSystem();
  m.cwd = m.root;

  while(scanf("%s", command) > 0){
    if(strcmp(command, "mkdir") == 0){
      scanf("%s", path);
      mkdir(m, path);
    }

    else if(strcmp(command, "ls") == 0){
      if(getchar() == '\n')
        strcpy(path, "");
      else
        scanf("%s", path);

      ls(m, path);
    }
    
    else if(strcmp(command, "cd") == 0){
      scanf(" %s", path);
      cd(&m, path);
    }
    
    else if(strcmp(command, "touch") == 0){
      scanf(" %s", path );
      touch(m, path);
    }
    
    else if(strcmp(command, "pwd") == 0){
      pwd(m.cwd);
      printf("\n");
    }
    
    else if(strcmp(command, "rm") == 0){
        scanf(" %s", path);
        rm(m, path);
    }

    else if(strcmp(command, "find") == 0){
        char name[21];
        scanf(" %s", name);
        find(m.root, name);
    }
    else if (strcmp(command, "exit") == 0){
      return 0;
    }

    else{
      printf("\'%s\' is not a recognized command\n", command);
    }

  }

  return 0;
}

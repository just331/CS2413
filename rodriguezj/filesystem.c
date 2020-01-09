#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"


void errorMsg(char *msg){
  printf("%s\n", msg);
}

char *getLocalName(char *path, char *localName){
  while( (*path != '\0') && (*path != '/') ){
    *localName = *path;
    localName++;
    path++;
  }
  *localName = '\0';
  if(*path == '/')
    path++;

  return path;
}


char *getName(const char *p, char *leftPath){


  char *temp, *name;

  name = (char *) malloc(21 * sizeof(char));
  temp = name;

  if(*p == '/'){
    p++; 
    while(*p != '\n') *leftPath++ = *p++;
    return "/";
  }

  while(*p != '\n' && *p != '/') *temp++ = *p++;
  *temp = '\0';


  if(*p != '\n'){
    p++; 
    while(*p != '\n') *leftPath++ = *p++;
  }

  return name;


}



Node *newDirNode(char *name, Node *parent){

  Node *newNode;
  newNode = (Node *)malloc(sizeof(Node));

  strcpy(newNode->name.name, name);
  newNode->child = NULL;
  newNode->sibling = NULL;
  newNode->bit = 1; 
  newNode->parent = parent;

  return newNode;
}


Node *getNode(Node *cwd, char *p){

  if (strcmp(p, "..") == 0){
    if(cwd->parent != NULL)
      return cwd->parent;
    else
      return cwd;
  }
  if(strcmp(p, ".") == 0){
    return cwd;
  }
  Node *currNode = cwd->child;

  while((currNode != NULL) && (compareName(currNode->name.name, p) != 0)){
      currNode = currNode->sibling;
  }

  return currNode;
}



int lastDir(char *path){

  char *t = path;

  while((*t != '\n') && (*t != '/') && (*t != '\0')) t++;

  if(*t == '/' && *(t+1) != '\0')
    return 0;
  else
    return 1;


}

int compareName(const char *name1, const char *name2){
  const char *tChar1, *tChar2;
  tChar1 = name1;
  tChar2 = name2;

  while((compare(*tChar1, *tChar2) == 0) && (*tChar1 != '\0')){
    tChar1++;
    tChar2++;
  }
  if(compare(*tChar1, *tChar2) < 0)
    return -1;
  else if(compare(*tChar1, *tChar2) > 0)
    return 1;

  return 0;
}

int compare(char c1, char c2){
  if(c1 == c2)
    return 0;
  if(c1 == '\0')
    return -1;
  if(c2 == '\0')
    return 1;
  if(c1 == '.')
    return -1;
  if(c2 == '.')
    return 1;
  if(c1 == '-')
    return -1;
  if(c2 == '-')
    return 1;
  if(c1 == '_')
    return -1;
  if(c2 == '_')
    return 1;
  if(c1 < c2)
    return -1;
  else
    return 1;
}

void insertDir(Node *newDir, Node *parent){
  Node *currDir, *prevDir;
  prevDir = NULL;
  currDir = parent->child;

  if(currDir == NULL){
    parent->child = newDir;
  }

  else{

    while((currDir != NULL) && (compareName(currDir->name.name, newDir->name.name) < 0) && (currDir->bit != 0)){
      prevDir = currDir;
      currDir = currDir->sibling;
    }

    if(prevDir == NULL){
      newDir->sibling = parent->child;
      parent->child = newDir;
    }
    else{
      newDir->sibling = currDir;
      prevDir->sibling = newDir;
    }

  }
  return;
}

int dirExists(char *nodeName, Node *cwd){

  Node *currDir = cwd->child;
  if(currDir == NULL)
    return 0;
  if (compareName(nodeName, currDir->name.name) == 0){
    return 1;
  }
  else{

    currDir = currDir->sibling;
    while(currDir != NULL){

      if(compareName(nodeName, currDir->name.name) == 0){
        if(currDir->bit == 0)
          return 0;
        else
          return 1;
      }
      currDir = currDir->sibling;

    }

  }
  return 0;
}


int fileExists(char *fileName, Node *cwd){
  Node *currDir = cwd->child;

  if(currDir == NULL)
    return 0;

  if (compareName(fileName, currDir->name.name) == 0) {
    return 1;
  }

  else{
    currDir = currDir->sibling;
    while(currDir != NULL){

      if (compareName(fileName, currDir->name.name) == 0){
        return 1;
      }
      currDir = currDir->sibling;

    }
  }
  return 0;
}

Node *newFileNode(char *name, Node *parent){
  Node *newNode;
  newNode = (Node *)malloc(sizeof(Node));

  strcpy(newNode->name.name, name);
  newNode->child = NULL;
  newNode->sibling = NULL;
  newNode->bit = 0; 
  newNode->parent = parent;

  return newNode;

}

void insertFile(Node *newFile, Node *parent){
  Node *currNode, *prevNode;
  currNode = parent->child;
  prevNode = NULL;

  if(currNode == NULL){
    parent->child  = newFile;
    return;
  }

  else{

    while(currNode != NULL){
      if( (currNode->bit == 0) && (compareName(currNode->name.name, newFile->name.name) > 0) ){

        newFile->sibling = currNode;
        if(prevNode == NULL)
          parent->child = newFile;

        else
          prevNode->sibling = newFile;

        return;
      }
      prevNode = currNode;
      currNode = currNode->sibling;
    }

    prevNode->sibling = newFile;
    return;

  }
}

Node *newFileSystem(){

  Node *newNode = (Node *)malloc(sizeof(Node));
  strcpy(newNode->name.name, "/");
  newNode->child = NULL;
  newNode->sibling = NULL;
  newNode->bit = 1; 
  newNode->parent = NULL;
  return newNode;
}



void mkdir(md m, char *p){

  if(*p == '/')
    return createDir(m.root, ++p);
    return createDir(m.cwd, p);

}

void createDir(Node *cwd, char *p){

  char localName[21];
  Node *dirNode, *newDir;
  int m;
  m = lastDir(p);
  
  if(m == 1){ 
    dirNode = getNode(cwd, p);
    if(dirExists(p, cwd)){
      printf("Path Error: \'");
      pwd(dirNode);
      printf("\' already exists and cannot be created.\n");
      errorMsg("Make Dir Error: Cannot create directory.");
      return;
    }
    newDir = newDirNode(p, cwd);
    
    insertDir(newDir, cwd);
    return;
  }

  else{
    p = getLocalName(p, localName);
    dirNode = getNode(cwd, localName);



    if(dirNode == NULL){
      dirNode = newDirNode(localName, cwd);
      insertDir(dirNode, cwd);
    }
    else if(dirNode->bit == 0){
      printf("Path Error: Cannot create sub-directory content, \'");
      pwd(dirNode);
      printf("\' is a file.\n");
      errorMsg("Make Dir Error: Cannot create directory.");
      return;
    }

    createDir(dirNode, p);

  }

  return;
}

void ls(md m, char *path){

  if (strcmp(path, "") == 0){
    lsCWD(m.cwd);
  }
  else{
    if(*path == '/')
      list(m.root, ++path);
    else
      list(m.cwd, path);
  }
}


void list(Node *cwd, char *path){
  char localName[21];
  Node *dirNode;
  int i;

  i = lastDir(path);

  if(i){

      dirNode = getNode(cwd, path);
      if(dirNode == NULL){
        printf("Path Error: directory \'" );
        pwd(cwd);
        if(cwd->parent != NULL)
          printf("/%s\' does not exist.\n", path);
        else
          printf("%s\' does not exist.\n", path);

        errorMsg("List Error: Cannot perform list operation.");
        return;
      }

      if(dirNode->bit == 0){
        printf("Cannot create sub-directory content. \'");
        pwd(dirNode);
        printf("\' is a file.\n" );
        printf("List Error: Cannot perform list operation. \'");
        pwd(dirNode);
        printf("\' is file.\n");
        return;
      }

    lsCWD(dirNode); 
  }

  else{
    path = getLocalName(path, localName);
    dirNode = getNode(cwd, localName);

    if(dirNode == NULL){
      printf("Path Error: directory \'");
      pwd(cwd);
      printf("/%s\' does not exist.\n", localName);
      errorMsg("List Error: Cannot perform list operation.");
      return;
    }
    else if(!dirNode->bit){
      printf("Path Error: Cannot create sub-directory content, \'");
      pwd(dirNode);
      printf("\' is a file.\n");
      errorMsg("List Error: Cannot perform list operation.");
      return;
    }
    list(dirNode, path);
  }

  return;
}

void lsCWD(Node *cwd){
  Node *printerNode;

  printerNode = cwd->child;

  printf("Listing for \'" );
  pwd(cwd);
  printf("\'" );

  printf("\n" );
  while(printerNode != NULL){
    if(printerNode->bit == 1)
      printf("D ");
    else
      printf("F ");

    printf("%s\n", printerNode->name.name);
    printerNode = printerNode->sibling;
  }
}


void touch(md m, char *path){

  if(*path == '/')
    createFile(m.root, ++path);
  else
    createFile(m.cwd, path);

  return;
}


void createFile(Node *cwd, char *path){
  char localName[21];
  Node *dirNode, *newFile;
  int i;

  i = lastDir(path);

  if(i){ 
    dirNode = getNode(cwd, path);
    if(fileExists(path, cwd)){
      printf("Path Error: \'");
      pwd(dirNode);
      printf("\' already exists and cannot be created.\n");
      errorMsg("Touch Error: Cannot create file.");
      return;
    }

    newFile = newFileNode(path, cwd);
    insertFile(newFile, cwd);
    return ;
  }

  else{
    path = getLocalName(path, localName);
    dirNode = getNode(cwd, localName);


    if(dirNode == NULL){
      dirNode = newDirNode(localName, cwd);
      insertDir(dirNode, cwd);
    }
    else if(dirNode->bit == 0){
      printf("Path Error: Cannot create sub-directory content, \'");
      pwd(dirNode);
      printf("\' is a file.\n");
      errorMsg("Error Output: Touch Error: Cannot create file.");
      return;
    }

    createFile(dirNode, path);
  }

  return;
}

void cd(md *m, char *path){
  if(*path == '/' && *(path + 1) == '\0')
    m->cwd = m->root;
  else if(*path == '/')
    changeDir(m, m->root, ++path);
  else
    changeDir(m, m->cwd, path);
  return;
}

void changeDir(md *m, Node *cwd, char *path){
  Node *newCWD;
  char localName[21];

  int i;
  i = lastDir(path);

  if(i){
    path = getLocalName(path, localName);
    newCWD = getNode(cwd, localName);

    if(newCWD == NULL){
      printf("Path Error: directory \'" );
      pwd(cwd);
      if(cwd->parent != NULL)
        printf("/%s\' does not exist.\n", path);
      else
        printf("%s\' does not exist.\n", localName);

      errorMsg("Change Dir Error: Cannot change working directory.");
      return;
    }
    if(newCWD->bit == 0){
      printf("Cannot create sub-directory content. \'");
      pwd(newCWD);
      printf("\' is a file.\n" );
      errorMsg("Change Dir Error: Cannot change working directory.");
    }

    else{
      m->cwd = newCWD;
      return;
    }
  }

  else{
    path = getLocalName(path, localName);
    newCWD = getNode(cwd, localName);

    if(newCWD == NULL){
      printf("Path Error: directory \'");
      pwd(cwd);
      printf("/%s\' does not exist.\n", localName);
      errorMsg("Change Dir Error: Cannot change working directory.");
      return;
    }
    if(newCWD->bit == 0){
      printf("Path Error: Cannot create sub-directory content, \'");
      pwd(newCWD);
      printf("\' is a file.\n");
      errorMsg("Change Dir Error: Cannot change working directory.");
      return;
    }
    else{

      changeDir(m, newCWD, path);
    }
  }
}

void pwd(Node *n){
  if(n->parent == NULL)
    printf("/" );
  else
    recPrintAbsPath(n);
  return;
}

void recPrintAbsPath(Node *n){
  if(n->parent != NULL){
    recPrintAbsPath(n->parent);
    printf("/%s", n->name.name);
  }

}

void find(Node *node, char *name){
  Node *child;

  if(node == NULL) return;


  if(strstr(node->name.name, name) != NULL){

    if(node->bit == 1)
      printf("D ");
    else
      printf("F ");

    pwd(node);
    printf("\n" );
  }

  child = node->child;
  while(child != NULL){
    find(child, name);
    child = child->sibling;
  }

}


void rm(md m, char *path){
  if(*path == '-'){
    getchar();
    scanf(" %s", path);

    if(*path == '/')
      fRemove(m.root, ++path);
    else
      fRemove(m.cwd, path);

    return;
  }

  else{
    if(*path == '/')
      removeNode(m.root, ++path);
    else
      removeNode(m.cwd, path);
  }
}

void removeNode(Node *cwd, char *path){
  char localName[21];
  Node *dirNode, *currNode;
  int i;

  i = lastDir(path);

  if(i){
    dirNode = getNode(cwd, path);
    if(dirNode == NULL){
      printf("Path Error: directory \'" );
      pwd(cwd);
      if(cwd->parent != NULL)
        printf("/%s\' does not exist.\n", path);
      else
        printf("%s\' does not exist.\n", path);

      errorMsg("Remove Error: Cannot remove file or directory.");
      return;
    }
    if(dirNode->child != NULL){
      printf("Remove Error: directory \'" );
      pwd(dirNode);
      printf("\' is not empty\n" );
      return;
    }
    if(cwd->child == dirNode){
      cwd->child = dirNode->sibling;
    }

    else{
      currNode = cwd->child;
      while(currNode->sibling != dirNode)
        currNode = currNode->sibling;

      currNode->sibling = dirNode->sibling;
    }
    free(dirNode);
  }

  else{
    path = getLocalName(path, localName);
    dirNode = getNode(cwd, localName);

    if(dirNode == NULL){
      printf("Path Error: directory \'" );
      pwd(cwd);
      printf("/%s\' does not exist.\n", localName);
      errorMsg("Remove Error: Cannot remove file or directory.");
      return;
    }

    else if(!dirNode->bit){
      printf("Path Error: Cannot create sub-directory content, \'");
      pwd(dirNode);
      printf("\' is a file.\n");
      errorMsg("Remove Error: Cannot remove file or directory.");
      return;
    }
    removeNode(dirNode, path);
  }

}

void fRemove(Node *cwd, char *path){
  char localName[21];
  Node *dirNode, *currNode;
  int i;

  i = lastDir(path);

  if(i){

    dirNode = getNode(cwd, path);
    if(dirNode == NULL){
      printf("I am here\n" );
      printf("Path Error: directory \'" );
      pwd(cwd);
      if(cwd->parent != NULL)
        printf("/%s\' does not exist.\n", path);
      else
        printf("%s\' does not exist.\n", path);

      errorMsg("Remove Error: Cannot remove file or directory.");
      return;
    }
    if((!dirNode->bit) || (dirNode->child == NULL)){
      if(cwd->child == dirNode){
        cwd->child = dirNode->sibling;
      }

      else{
        currNode = cwd->child;
        while(currNode->sibling != dirNode){
          currNode = currNode->sibling;
        }

        currNode->sibling = dirNode->sibling;
      }

      free(dirNode);
      return;
    }

    recRemove(dirNode);
  }

  else{
    path = getLocalName(path, localName);
    dirNode = getNode(cwd, localName);

    if(dirNode == NULL){
      printf("Path Error: directory \'" );
      pwd(cwd);
      printf("/%s\' does not exist.\n", localName);
      errorMsg("Remove Error: Cannot remove file or directory.");
      return;
    }

    else if(!dirNode->bit){
      printf("Path Error: Cannot create sub-directory content, \'");
      pwd(dirNode);
      printf("\' is a file.\n");
      errorMsg("Remove Error: Cannot remove file or directory.");
      return;
    }
    fRemove(dirNode, path);

  }
}

void recRemove(Node *dirNode){
  Node *currNode;
  while(dirNode->child != NULL)
    recRemove(dirNode->child);

  if(dirNode->parent->child == dirNode)
    dirNode->parent->child = dirNode->sibling;

  else{
    currNode = dirNode->parent->child;
    while(currNode->sibling != dirNode)
      currNode = currNode->sibling;

    currNode->sibling = dirNode->sibling;
  }

  free(dirNode);
  return;

}


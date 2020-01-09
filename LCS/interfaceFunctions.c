#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "helperFunctions.h"
#include "interfaceFunctions.h"

Node *initFileSystemRoot(){
  /*
    Creates a root directory
  */
  Node *newNode;
  newNode = (Node *)malloc(sizeof(Node));

  strcpy(newNode->name.name, "/");
  newNode->fChild = NULL;
  newNode->sibling = NULL;
  newNode->type = 1; //1 denotes a dir and 0 denotes a file
  newNode->parent = NULL;

  return newNode;
}

/*************MKDIR***********************/

void mkdir(meta m, char *p){

  if(*p == '/')//Absolute Path
    return createDir(m.root, ++p);
  //else // Relative Path
    return createDir(m.cwd, p);

}

void createDir(Node *cwd, char *p){

  char localName[21];
  Node *dirNode, *newDir;
  int m;
  //printf("The path is %s\nAnd the name of cwd is %s\n", p, cwd->name.name);
  m = lastDir(p);
  //printf("The value of m is %d\n", m );
  //BASE CASE
  if(m == 1){ //If last directory in path
    //printf("I am in base case\n" );
    //dirName = getName(p, leftPath); //In case lastDir has '/' at the end
    dirNode = getNode(cwd, p);
    if(dirExists(p, cwd)){
      printf("Path Error: \'");
      pwd(dirNode);
      printf("\' already exists and cannot be created.\n");
      errorMsg("Make Dir Error: Cannot create directory.");
      return;
    }
    newDir = newDirNode(p, cwd); //Create dir
    //Now insert it in the right position in the root dir
    insertDir(newDir, cwd);
    //printf("The Node has been created.\nProof %s\nThe parent is %s\n", newDir->name.name, newDir->parent->name.name);
    return;
  }


  //RECURSIVE CASE
  else{
    //printf("I am in the RECURSIVE case\n" );
    //dirName = getName(p, leftPath); //Get the first dir in path
    p = getLocalName(p, localName);
    //printf("mkdir: The leftover path is %s\n", leftPath);
    //printf("mkdir: The name of first directory in the path is %s\n",dirName);
    dirNode = getNode(cwd, localName);



    if(dirNode == NULL){
      dirNode = newDirNode(localName, cwd);
      insertDir(dirNode, cwd);
    }
    else if(dirNode->type == 0){
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

/*************LS*****************/
void ls(meta m, char *path){

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

  if(i){//Last content in path

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

      if(dirNode->type == 0){
        printf("Cannot create sub-directory content. \'");
        pwd(dirNode);
        printf("\' is a file.\n" );
        printf("List Error: Cannot perform list operation. \'");
        pwd(dirNode);
        printf("\' is file.\n");
        return;
      }

    lsCWD(dirNode); //??????????????????????????????THIS OR cwd->parent??????????
  }

  else{
    path = getLocalName(path, localName);
    dirNode = getNode(cwd, localName);

    if(dirNode == NULL){
      printf("Path Error: directory \'");
      // printf("I am exiting here...\n" );
      pwd(cwd);
      printf("/%s\' does not exist.\n", localName);
      errorMsg("List Error: Cannot perform list operation.");
      return;
    }
    else if(!dirNode->type){
      printf("Path Error: Cannot create sub-directory content, \'");
      pwd(dirNode);
      printf("\' is a file.\n");
      errorMsg("List Error: Cannot perform list operation.");
      // printf("List Error: Cannot perform list operation. \'");
      // pwd(dirNode);
      // printf("\' is file.\n");
      return;
    }
    list(dirNode, path);
  }

  return;
}

void lsCWD(Node *cwd){
  /*
    Take in the cwd and while the sibling is not NULL
    Print the names of the file on new line;
  */

  Node *printerNode;

  printerNode = cwd->fChild;

  printf("Listing for \'" );
  pwd(cwd);
  printf("\'" );

  printf("\n" );
  while(printerNode != NULL){
    if(printerNode->type == 1)
      printf("D ");
    else
      printf("F ");

    printf("%s\n", printerNode->name.name);
    printerNode = printerNode->sibling;
  }
}

/****************TOUCH***************/

void touch(meta m, char *path){

  if(*path == '/')
    createFile(m.root, ++path);
  else
    createFile(m.cwd, path);

  return;
}


void createFile(Node *cwd, char *path){
  //printf("The cwd is %s\nThe path is %s\n", cwd->name.name, path);

  //char *dirName,
  char localName[21];
  Node *dirNode, *newFile;
  int i;

  i = lastDir(path);

  if(i){ //It is the name of file
    //printf("touch: It is the last thing in path = \"%s\"\n", path);
    dirNode = getNode(cwd, path);
    if(fileExists(path, cwd)){
      printf("Path Error: \'");
      pwd(dirNode);
      printf("\' already exists and cannot be created.\n");
      errorMsg("Touch Error: Cannot create file.");
      return;
    }

    //printf("touch: The name of the file to be created is %s and cwd is %s\n", path, cwd->name.name);
    newFile = newFileNode(path, cwd);
    insertFile(newFile, cwd);
    return ;
  }

  else{ //It is not the file
    //dirName = getName(path, leftPath);
    path = getLocalName(path, localName);
    dirNode = getNode(cwd, localName);


    if(dirNode == NULL){
      dirNode = newDirNode(localName, cwd);
      //printf("touch: New dir created with name %s and parent %s\n", dirNode->name.name, cwd->name.name);
      insertDir(dirNode, cwd);
      // printf("touch: New dir inserted with name %s and parent %s\n", dirNode->name.name, cwd->name.name);
    }
    else if(dirNode->type == 0){
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


/****************************CD******************************/
void cd(meta *m, char *path){
  if(*path == '/' && *(path + 1) == '\0')
    m->cwd = m->root;
  else if(*path == '/')
    changeDir(m, m->root, ++path);
  else
    changeDir(m, m->cwd, path);
  return;
}

void changeDir(meta *m, Node *cwd, char *path){
  Node *newCWD;
  char localName[21];
  // printf("changeDir: The cwd is %s and the path is %s\n", cwd->name.name, path);

  int i;
  i = lastDir(path);
  //printf("changeDir: The value of i is %d\n", i);

  if(i){//lastDir in path
    path = getLocalName(path, localName);
    newCWD = getNode(cwd, localName);
    //printf("I get out of getNode function\n" );
    //printf("The newCWD is %s\n", newCWD->name.name);

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
    if(newCWD->type == 0){
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

  else{//not lastDir in path
    path = getLocalName(path, localName);
    newCWD = getNode(cwd, localName);

    if(newCWD == NULL){
      printf("Path Error: directory \'");
      // printf("I am exiting here...\n" );
      pwd(cwd);
      printf("/%s\' does not exist.\n", localName);
      errorMsg("Change Dir Error: Cannot change working directory.");
      return;
    }
    if(newCWD->type == 0){
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

/****************PWD********************/
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

/************FIND*********************/
void find(Node *node, char *name){
  Node *child;

  if(node == NULL) return;


  if(strstr(node->name.name, name) != NULL){

    if(node->type == 1)
      printf("D ");
    else
      printf("F ");

    pwd(node);
    printf("\n" );
  }

  child = node->fChild;
  while(child != NULL){
    find(child, name);
    child = child->sibling;
  }

}

/******************REMOVE*******************/
void rm(meta m, char *path){
  if(*path == '-'){//rm -f
    //FORCE REMOVE
    getchar();
    scanf(" %s", path);

    if(*path == '/')
      fRemove(m.root, ++path);
    else
      fRemove(m.cwd, path);

    return;
  }

  else{//simple remove
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

  if(i){//Remove this Node
    dirNode = getNode(cwd, path);
    if(dirNode == NULL){//When the node does not exist
      printf("Path Error: directory \'" );
      pwd(cwd);
      if(cwd->parent != NULL)
        printf("/%s\' does not exist.\n", path);
      else
        printf("%s\' does not exist.\n", path);

      errorMsg("Remove Error: Cannot remove file or directory.");
      return;
    }
    if(dirNode->fChild != NULL){//When the dir is not empty
      printf("Remove Error: directory \'" );
      pwd(dirNode);
      printf("\' is not empty\n" );
      return;
    }
    //Actual Removing the Node
    if(cwd->fChild == dirNode){//If Node is fChild
      cwd->fChild = dirNode->sibling;
    }

    else{//If Node is not the fChild
      currNode = cwd->fChild;
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

    else if(!dirNode->type){//It's a file
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
    if(dirNode == NULL){//When the node does not exist
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
    if((!dirNode->type) || (dirNode->fChild == NULL)){//Either a file or empty dir
      // printf("I am in second if\n" );
      if(cwd->fChild == dirNode){//If Node is fChild
        cwd->fChild = dirNode->sibling;
      }

      else{//If Node is not the fChild
        currNode = cwd->fChild;
        while(currNode->sibling != dirNode){
          currNode = currNode->sibling;
        }

        currNode->sibling = dirNode->sibling;
      }

      free(dirNode);
      return;
    }

    //ACTUAL Removal
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

    else if(!dirNode->type){//It's a file
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
  while(dirNode->fChild != NULL)
    recRemove(dirNode->fChild);

  if(dirNode->parent->fChild == dirNode)
    dirNode->parent->fChild = dirNode->sibling;

  else{
    currNode = dirNode->parent->fChild;
    while(currNode->sibling != dirNode)
      currNode = currNode->sibling;

    currNode->sibling = dirNode->sibling;
  }

  free(dirNode);
  return;

}

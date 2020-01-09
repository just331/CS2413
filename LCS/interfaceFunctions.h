#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <stdio.h>
#include "element.h"
#include "helperFunctions.h"

Node *initFileSystemRoot();

//mkdir functions
void mkdir(meta m, char *p);
void createDir(Node *cwd, char *p);

//ls function
void ls(meta m, char *path);
void list(Node *cwd, char *path);
void lsCWD(Node *cwd);

//touch function
void touch(meta m, char *path);
void createFile(Node *cwd, char *path);

//cd function
void cd(meta *m, char *path);
void changeDir(meta *m, Node *cwd, char *path);

//pwd
void pwd(Node *n);
void recPrintAbsPath(Node *n);

//find
void find(Node *n, char *name);

//rm
void rm(meta m, char *path);
void removeNode(Node *cwd, char *path);
void fRemove(Node *cwd, char *path);
void recRemove(Node *dirNode);

#endif

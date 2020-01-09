#ifndef _filesystem_H_
#define _filesystem_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _nodeName Name;
struct _nodeName{
  char name[21];
};

typedef struct _dirStruct Node;
struct _dirStruct{
  Node *child;
  Node *sibling;
  Node *parent;
  Name name;
  int bit; 
};

typedef struct _metadata md;
struct _metadata{
  Node *root;
  Node *cwd;
};


void errorMsg(char *);
Node * newDirNode(char*, Node*);
char *getName(const char *, char *);
char *getLocalName(char *, char *);
Node *getNode(Node *, char *);
int compareName(const char *, const char *);
int compare(char , char);
int lastDir(char *);
void insertDir(Node *, Node *);
int dirExists(char *, Node *);
int fileExists(char *, Node *);
Node *newFileNode(char *, Node *);
void insertFile(Node *, Node *);
void lsCWD(Node *);
Node *newFileSystem();
void mkdir(md, char *);
void createDir(Node *, char *);
void ls(md, char *);
void list(Node *, char *);
void lsCWD(Node *);
void touch(md, char *);
void createFile(Node *, char *);
void cd(md *, char *);
void changeDir(md *, Node *, char *);
void pwd(Node *);
void recPrintAbsPath(Node *);
void find(Node *, char *);
void rm(md, char *);
void removeNode(Node *, char *);
void fRemove(Node *, char *);
void recRemove(Node *);


#endif

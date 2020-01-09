#ifndef _HELPERFUNCTION_H_
#define _HELPERFUNCTION_H_

#include "element.h"

void errorMsg(char *);

Node * newDirNode(char *name, Node *parent);

char *getName(const char *p, char *leftPath);

char *getLocalName(char *path, char *localName);

Node *getNode(Node *cwd, char *p);

int compareName(const char *name1, const char *name2);

int compareChar(char c1, char c2);

int lastDir(char *path);

void insertDir(Node *newDir, Node *parent);

int dirExists(char *nodeName, Node *cwd);

int fileExists(char *fileName, Node *cwd);

Node *newFileNode(char *name, Node *parent);

void insertFile(Node *newFile, Node *parent);

void lsCWD(Node *cwd);

//DELETE THIS
Node *tempFunction(meta m);

#endif

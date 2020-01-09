#ifndef __EXECUTE_H__
#define __EXECUTE_H__

#include "stdheader.h"

// Check windows
#if _WIN32 || _WIN64
#include <process.h>
#define __WINDOWS__
#if _WIN64
#include <process.h>
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__ 
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check MINGW
#if __MINGW64__ || __MINGW32__ 
#define __MINGW__
#endif



int execute_command(char **, char*, char* , char*);

#endif
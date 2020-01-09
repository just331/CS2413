#ifndef ___GRADE_H__
#define ___GRADE_H__	

#include "stdheader.h"

/* reset()
- deletes all files except for the .c and .h files in every subdirectory.
- deletes all files in comparison directory
*/
void reset();

/* makedirs()
- creates "reference" directory
- creates "comparison" directory
- For every (last, first) pair of names in roster.txt
---- create the directory called "lastname"+"first initial")
*/
void makedirs();

/* reference()
- compile the .c files in the reference directory into an executable. 
- follows test script with reference executable to generate "expected" output. 
*/
void reference();


/* grade()
- For each student in the roster
---- compile .c files into executable, record result in gradebook.
---- Execute the test script and compile results in gradebook. 
---- calculate the grade for the student. 
*/
void grade();

/* prepcompare()
- create "comparison" directory
- For each student in the roster
---- prepend .c files with student lastname-first-initial
---- copy new .c files to comparison directory.  
*/
void setupcompare();

#endif
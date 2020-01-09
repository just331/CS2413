/* ===================================================

Grading Script
Author: Edward Wertz

Functionality: 
0) Delete all files in directories except ".c" and ".h" files.  
1) From roster create a directory for each student and reference implementation directory.  
2) Enter each directory and compile all ".c" files into a single executable
3) Follow Testing Script with reference program to generate expected output for test cases. 
4) Test each student program with test cases and compare to expected output from reference
5) Compile results and give numeric grade, output to a CSV file.
6) Prep ".c" files for comparison by moving files to common directory and prepending student name to files.  

Execute Functionality:
0) grade.exe reset - restore state prior to executing 2-6   
1) grade.exe makedirs
2) grade.exe compile
3) grade.exe reference
4) grade.exe test
5) grade.exe assess
6) grade.exe prepcompare


Format For Roster File: roster.txt
----------------------
lastname1 firstname1
lastname2 firstname2 
...

The roster is a sequence of pairs of tokens. The first token in a pair is the student's lastname.  
The second token is the student's first name.  The next token is the last name of the next student.  

Format For Testing Script: testscript.txt
-------------------------
Name_Of_Test_Input_File
Command Line Args (minus program name)
Name_Of_Test_Input_File
Command Line Args (minus program name)

CONSTANTS
=========
MAX_STUDENTS = 200


=================================================== */

#include "grade.h"


//LOCAL FUNCTION DECLARATIONS
void printUsage(int, char**);


int main (int argc, char ** argv){
	
	if(argc != 2){
		printUsage(argc, argv);
		return 0;
	}
	
	if(strcmp(argv[1], "reset") == 0){
		reset();
	} else 
	if(strcmp(argv[1], "makedirs") == 0){
		makedirs();
	} else 
	if(strcmp(argv[1], "reference") == 0){
		reference();
	} else 
	if(strcmp(argv[1], "grade") == 0){
		grade();
	} else 
	if(strcmp(argv[1], "setupcompare") == 0){
		setupcompare();
	} else 
		printUsage(argc, argv);
	
	return 0;	
}

void printUsage(int argc, char ** argv){
	printf("Usage:\n");
	printf("%s reset - reset grading state\n", argv[0]);
	printf("%s makedirs - make directories from roster\n", argv[0]);
	printf("%s reference - create expected output from reference\n", argv[0]);
	printf("%s grade - execute testing scripts\n", argv[0]);
	printf("%s prepcompare - prepare soure files and copy to common directory\n", argv[0]);
}

/*

{
  DIR *dp;
  struct dirent *ep;

  dp = opendir ("./");
  if (dp != NULL)
    {
      while (ep = readdir (dp))
        puts (ep->d_name);
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");

  return 0;
}

*/
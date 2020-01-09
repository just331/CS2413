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
MAX_NAME_LENGTH = 30


=================================================== */

#ifndef __GRADE_BOOK_H__
#define __GRADE_BOOK_H__


#include "stdheader.h"

#define MAX_STUDENTS 100
#define MAX_TESTS 20 
#define MAX_NAME_LENGTH 30
#define COMMANDLINE_LENGTH 81

// DATA TYPES

//Student
struct _student_name{
	char first[MAX_NAME_LENGTH];
	char last[MAX_NAME_LENGTH];
};

typedef struct _student_name student_name_type;
typedef struct _student_name *student_name;

//Test
struct _test{
	char input[MAX_NAME_LENGTH]; // Name of Input File
	char cla[COMMANDLINE_LENGTH]; // Commandline Arguments
};

typedef struct _test test_type;
typedef struct _test *test;


//Gradebook Entry
struct _gradebook_entry{
	student_name_type student;
	double grades[MAX_TESTS];
	char compiled;
	double final_grade;
};

typedef struct _gradebook_entry gb_entry_type;
typedef struct _gradebook_entry *gb_entry;

//Gradebook
struct _gradebook{
	gb_entry_type entry[MAX_STUDENTS];
	int num_students;
  test_type tests[MAX_TESTS];
	int num_tests;
};

typedef struct _gradebook gradebook_type;
typedef struct _gradebook * gradebook;

// GRADE BOOK FUNCTIONS

void init_gradebook_from_roster(gradebook, FILE*);
//void load_gradebook(FILE*, gradebook);
void write_gradebook(FILE*, gradebook);
//void add_student(gradebook, char*, char*);
//void calc_final_grades(gradebook);



#endif

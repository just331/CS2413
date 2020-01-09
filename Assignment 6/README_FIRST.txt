This grading script is designed and written by Edward Wertz
Copyright 2016

Overview

STEPS (first get script working with contained files)

(1)  Populate "roster.txt"

1 student per line "lastname" space "firstname"

(2) Populat "testscript.txt"

1 test#.txt per line

(3) compile grading script in top level directory

gcc *.c -o grade.exe

(4) Make Sub-Directories

WINDOWS COMMAND: grade.exe makedirs  
MAC/LINUX/CYGWIN: ./grade.exe makedirs

(5) Copy reference source code to reference directory

(6) Make reference solution

WINDOWS COMMAND: grade.exe reference  
MAC/LINUX/CYGWIN: ./grade.exe reference

(7) Copy student implementations to student directories

(8) grade student submissions

WINDOWS COMMAND: grade.exe grade  
MAC/LINUX/CYGWIN: ./grade.exe grade

(9) review CSV file generated, review student submissions and grades

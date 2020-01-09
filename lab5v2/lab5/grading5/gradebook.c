#include "gradebook.h"


char first[100];
char last[100];

void init_gradebook_from_roster(gradebook gb, FILE* roster){
  int e;
  int t;
  //initialize gradebook to no students
  gb->num_students =0;
  for(e=0; e < MAX_STUDENTS; e++){
    int g;
    gb->entry[e].student.first[0] = '\0';
    gb->entry[e].student.last[0] = '\0';
    gb->entry[e].compiled = 0;
    gb->entry[e].final_grade= 0.0;
    for(g=0; g < MAX_TESTS; g++)
      gb->entry[e].grades[g] = 0;
  }
  //initialize tests to none.
  gb->num_tests = 0;
  for(t = 0; t < MAX_TESTS; t++){
    gb->tests[t].input[0] = '\0';
    gb->tests[t].cla[0] = '\0';
  }
  //read students from roster file. 
  e = 0;
  while((fscanf(roster, "%s", last) > 0) && (fscanf(roster, "%s", first) >0)){
    strcpy(gb->entry[e].student.first, first);
    strcpy(gb->entry[e].student.last, last);
    e++;
    gb->num_students=e;
  }
  //roster is closed in the same function which opened it. 
}




//void load_gradebook(FILE*, gradebook);
void write_gradebook(FILE*csv, gradebook gb){
  int index, test;
  fprintf( csv, "%s", "last");
  fprintf( csv, ", %s", "first");
  fprintf(csv, ", %s", "compiled");
  fprintf(csv, ", %s", "final grade");  
  for(test = 0; test < gb->num_tests; test++){
    fprintf(csv, ", test%d", test+1);
  }
  fprintf(csv, "\n");

  
  for(index = 0; index < gb->num_students; index++){
    fprintf( csv, "%s", gb->entry[index].student.last);
    fprintf( csv, ", %s", gb->entry[index].student.first);
    fprintf(csv, ", %d", gb->entry[index].compiled);
    fprintf(csv, ", %6.2f", gb->entry[index].final_grade);
    for(test = 0; test < gb->num_tests; test++){
      fprintf(csv, ", %6.2f", gb->entry[index].grades[test]);
    }
    fprintf(csv, "\n");
  }
  
}
//void add_student(gradebook, char*, char*);
//void calc_final_grades(gradebook);

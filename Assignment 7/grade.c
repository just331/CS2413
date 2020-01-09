
#include "grade.h"
#include "gradebook.h"
#include "execute.h"

gradebook_type gb;

//semi persistent variables. 
char top_dir_name[PATH_MAX];
char child_dir_name[PATH_MAX];
char filename[PATH_MAX];

DIR *top_dir;
struct dirent* top_entry;
struct stat st;

//Helper Function Prototypes
int EndsWith(const char *str, const char *suffix);
void copyFile(char* source, char *dest);
void compare_output(FILE*, FILE*, size_t *, size_t*);

/* reset()
- deletes all files except for the .c and .h files in every subdirectory.
- deletes all files in comparison directory
*/
void reset_dir(char *, char*);

void reset(){
  //Save Current (Top Level) Working Directory 
  if(!getcwd(top_dir_name, PATH_MAX))
    return; //could not set current working directory
  
  //Iterate Through Entries
  // Error checking omitted for expository purposes
  top_dir = opendir (top_dir_name);
	if (top_dir != NULL){
		while (top_entry = readdir (top_dir)){
      //get path to entry as string
      if(strcmp(top_entry->d_name, ".") == 0 || strcmp(top_entry->d_name, "..") == 0)
        continue;
      snprintf(child_dir_name, PATH_MAX, "%s/%s", top_dir_name, top_entry->d_name);
      //check if entry is a directory
      stat(child_dir_name, &st);
      if(S_ISDIR(st.st_mode))
      {
        reset_dir(child_dir_name, top_entry->d_name);// This directory entry is another directory
      }
    }
    closedir(top_dir);
  }
}

//given a sub-directory, reset its contents
void reset_dir(char * dir_name, char*local_dir_name){
  DIR* dir = opendir(dir_name);
  struct dirent * entry;
  if(!dir){
    printf("%s could not be opened as a directory\n", dir_name);
    return;
  }
  
  printf("resetting %s\n", dir_name);
  while(entry = readdir(dir)){
    //get path to entry
    snprintf(filename, PATH_MAX, "%s/%s", dir_name, entry->d_name);
    //check if entry is a directory
    stat(filename, &st);
    if(S_ISREG(st.st_mode))
    {
      if(strcmp(local_dir_name, "comparison") ==0){
        //delete everything in comparison directory
        printf("deleting: %s\n", filename);
        remove(filename);
      } else {
        //delete everything but c and h files
        if(!EndsWith(filename, ".c") && !EndsWith(filename, ".h")){
          printf("deleting: %s\n", filename);
          remove(filename); 
        }
      }
    }
  }
}


/* makedirs()
- creates "reference" directory
- creates "comparison" directory
- For every (last, first) pair of names in roster.txt
---- create the directory called "lastname"+"first initial")
*/
void makedirs(){
  int index;
  if(!getcwd(top_dir_name, PATH_MAX))
    return; //could not set current working directory
  
  
  FILE* roster = fopen("roster.txt", "r"); 
  if(!roster){
    printf("Could not open: 'roster.txt'\n");
    return;
  }
  
  init_gradebook_from_roster(&gb, roster); 
  
  for(index = 0; index < gb.num_students; index++){
    //create directory name
    snprintf(child_dir_name, PATH_MAX, "%s/%s%c", top_dir_name, gb.entry[index].student.last, gb.entry[index].student.first[0]);
#ifdef __MINGW__    
    //create directory mingw for windows outside of cygwin 
    if(mkdir(child_dir_name/*, (S_IRWXU /*| S_IRWXG | S_IRWXO)*/)==0)
#else
    //create directory with (R)ead, (W)rite, e(X)ecute for (U)ser, (G)roup, (O)ther 
    if(mkdir(child_dir_name, (S_IRWXU | S_IRWXG | S_IRWXO))==0)
#endif
      printf("created: %s\n", child_dir_name);
    else
      printf("did not create:  %s\n", child_dir_name);
  }
  
  fclose(roster);
  
  //create reference directory
  snprintf(child_dir_name, PATH_MAX, "%s/%s", top_dir_name, "reference");
#ifdef __MINGW__    
  //create directory mingw for windows outside of cygwin 
  if(mkdir(child_dir_name/*, (S_IRWXU /*| S_IRWXG | S_IRWXO)*/)==0)
#else
  //create directory with (R)ead, (W)rite, e(X)ecute for (U)ser, (G)roup, (O)ther 
  if(mkdir(child_dir_name, (S_IRWXU | S_IRWXG | S_IRWXO))==0)
#endif
    printf("created: %s\n", child_dir_name);
  else
    printf("did not create:  %s\n", child_dir_name);
  
  //create comparison directory
  snprintf(child_dir_name, PATH_MAX, "%s/%s", top_dir_name, "comparison");
#ifdef __MINGW__    
  //create directory mingw for windows outside of cygwin 
  if(mkdir(child_dir_name/*, (S_IRWXU /*| S_IRWXG | S_IRWXO)*/)==0)
#else
  //create directory with (R)ead, (W)rite, e(X)ecute for (U)ser, (G)roup, (O)ther 
  if(mkdir(child_dir_name, (S_IRWXU | S_IRWXG | S_IRWXO))==0)
#endif
    printf("created: %s\n", child_dir_name);
  else
    printf("did not create:  %s\n", child_dir_name);
}

/* reference()
- compile the .c files in the reference directory into an executable. 
- follows test script with reference executable to generate "expected" output. 
*/
void reference(){
  int num_args;
  char input[200];
  char output[200];
  char * command[20];
  char cfiles[20][20];
  DIR* dp;
  struct dirent *ep; 
  FILE * testscript;
  if(!getcwd(top_dir_name, PATH_MAX))
    return; //could not set current working directory
  snprintf(child_dir_name, PATH_MAX, "%s/%s", top_dir_name, "reference");
  
  //change directory to reference
  if(0 != chdir(child_dir_name)){
    printf("Could not change dir to: %s\n", child_dir_name);
    return;
  }
  
  //Compile Reference Solution Arguments
    printf("Compiling Student Solution.....\n");
    num_args = 0;
    command[num_args] = "gcc";
    num_args++;
    command[num_args] = "-Wall";
    num_args++;
  //  command[num_args] = "-O3";
  //  num_args++;
    dp = opendir("./");
    if( dp != NULL){
      int i = 0;
      while(ep = readdir(dp)){
        strcpy(cfiles[i], ep->d_name);
        if(EndsWith(ep->d_name, ".c")){
          command[num_args] = cfiles[i];
          printf("c file: %s\n", command[num_args]);
          num_args++;
          i++;
        }
      }
      closedir(dp);
    } 
    command[num_args] = "-o";
    num_args++;
    command[num_args] = "ref.exe";
    num_args++;
    command[num_args] = (char *)NULL;

 
  //compile
  printf("Compiling Reference Solution\n");
  if(0 != execute_command(command, (char *)NULL, "compile_output.txt", "compile_error.txt"))
    printf("Compilation Failed\n");
  else 
    printf("Compilation Successful\n");
   
#ifdef __MINGW__
  command[0] = "ref.exe";
#else
  command[0] = "./ref.exe";
#endif
  num_args = 1;
  command[num_args] = (char *) NULL;
  
  //open test script
  testscript = fopen("../testscript.txt", "r");
  if(testscript == NULL)
    printf("Could not open %s\n", "../testscript.txt");
  input[0] = '.';
  input[1] = '.';
  input[2] = '/';
  while(fscanf(testscript, "%s", input+3) > 0){
    //if(input[pos] == '\n')
    // input[pos] = '\0';
    snprintf(output,200,"%s_%s", "expected", input+3);
    //copyFile(input, input+3);
    printf("Testing %s, writing to %s\n",input, output);
    execute_command(command, input, output, NULL); //execute test
  }
  fclose(testscript);
  
  //go back to top directory
	if(0 != chdir(top_dir_name)){
    printf("Could not change dir to: %s\n", top_dir_name);
    return;
  }
}

/* grade()
- For each student in the roster
---- compile .c files into executable, record result in gradebook.
---- Execute the test script and compile results in gradebook. 
---- calculate the grade for the student. 
*/
void grade(){  
  int compiled;
  int num_args, index;
  char cfiles[20][20];
  DIR* dp;
  struct dirent *ep; 
  char input[200];
  char temp[200];
  char output[200];
  char * command[20];
  FILE * testscript;
  FILE * gradebookcsv;
  if(!getcwd(top_dir_name, PATH_MAX))
    return; //could not set current working directory
  FILE* roster = fopen("roster.txt", "r"); 
  if(!roster){
    printf("Could not open: 'roster.txt'\n");
    return;
  }
  
  init_gradebook_from_roster(&gb, roster); 
  fclose(roster);
  
 
  for(index = 0; index < gb.num_students; index++){
    printf("\n----------------------------------------\n");
    printf("Grading Student %s, %s\n", gb.entry[index].student.last, gb.entry[index].student.first);
    printf("----------------------------------------\n");
    snprintf(child_dir_name, PATH_MAX, "%s/%s%c", top_dir_name, gb.entry[index].student.last, gb.entry[index].student.first[0]);
    //change directory
    if(0 != chdir(child_dir_name)){
      printf("Could not change dir to: %s\n", child_dir_name);
      return;
    }

    //Compile Reference Solution Arguments
    printf("Compiling Student Solution.....\n");
    num_args = 0;
    command[num_args] = "gcc";
    num_args++;
    command[num_args] = "-Wall";
    num_args++;
  //  command[num_args] = "-O3";
  //  num_args++;
    dp = opendir("./");
    if( dp != NULL){
      int i = 0;
      while(ep = readdir(dp)){
        strcpy(cfiles[i], ep->d_name);
        if(EndsWith(ep->d_name, ".c")){
          command[num_args] = cfiles[i];
          printf("c file: %s\n", command[num_args]);
          num_args++;
          i++;
        }
      }
      closedir(dp);
    } 
    command[num_args] = "-o";
    num_args++;
    command[num_args] = "prog.exe";
    num_args++;
    command[num_args] = (char *)NULL;

    //compile
    if(0 == execute_command(command, (char *)NULL, "compile_output.txt", "compile_error.txt")){
      int num_tests = 0;
      printf("COMPILE SUCCESS\n");
      gb.entry[index].compiled = 100;
#ifdef __MINGW__
      command[0] = "prog.exe";
#else
      command[0] = "./prog.exe";
#endif
      num_args = 1;
      command[num_args] = (char *) NULL;
      
  
      //open test script
      testscript = fopen("../testscript.txt", "r");
      if(testscript == NULL)
        printf("Could not open %s\n", "../testscript.txt");
      input[0] = '.';
      input[1] = '.';
      input[2] = '/';
      while(fscanf(testscript, "%s", input+3) > 0){
        //if(input[pos] == '\n')
        // input[pos] = '\0';
        snprintf(output,200,"%s_%s", "output", input+3);
        //copyFile(input, input+3);
      
        if(0 == execute_command(command, input, output, NULL)){ //execute test
          char reference[200];
          char rToken[200], sToken[200];
          size_t rc, sc, match, total;
          FILE * soutput, * routput;
          match = 1;
          total = 1;
          soutput = fopen(output, "r");
          snprintf(reference, 200, "../reference/expected_%s", input+3);
          routput = fopen(reference, "r");
          compare_output(routput, soutput, &total, &match);
          /*
          rc = fscanf(routput, "%200s", rToken);
          sc = fscanf(soutput, "%200s", sToken); 
          while(( rc == 1) &&( sc  == 1 )){
            total++;
            if(strcmp(rToken, sToken) == 0)
              match++;
          rc = fscanf(routput, "%200s", rToken);
          sc = fscanf(soutput, "%200s", sToken);
          }            
          while( rc  == 1){
            total++;
            rc = fscanf(routput, "%200s", rToken);
          }          
          while( sc  == 1){
            total++;
            sc = fscanf(soutput, "%200s", sToken);
          }
          */
          fclose(routput);
          fclose(soutput);
          gb.entry[index].grades[num_tests] = ((float)match)* 100.0/((float)total) ;
          printf("Testing %s ........PASSED %6.2f%%\n",input+3, gb.entry[index].grades[num_tests]);
        } else {
          gb.entry[index].grades[num_tests] = 0.0;
          printf("Testing %s ........FAILED\n", input+3);
        }
        num_tests++;
        if(gb.num_tests < num_tests) gb.num_tests = num_tests;
      }
      fclose(testscript);   
      //calculate student final grade;
      gb.entry[index].final_grade = 0;
      for(num_tests = 0; num_tests < gb.num_tests; num_tests++){
        gb.entry[index].final_grade += gb.entry[index].grades[num_tests];
      }
      gb.entry[index].final_grade  = gb.entry[index].final_grade/((float) num_tests);
      printf("FINAL RESULT %6.2f%%\n-------------------\n\n", gb.entry[index].final_grade); 
    } else {
      printf("FAILED\n");
      gb.entry[index].compiled = 0;
      gb.entry[index].final_grade = 0.0;
    }
    if(0 != chdir(top_dir_name)){
      printf("Could not change dir to: %s\n", top_dir_name);
      return;
    }
    
    //go back to top directory
    if(0 != chdir(top_dir_name)){
      printf("Could not change dir to: %s\n", top_dir_name);
      return;
    }
  }
  
  gradebookcsv = fopen("grades.csv", "w");
  printf("writing to grades.csv\n");
  write_gradebook(gradebookcsv, &gb);
  fclose(gradebookcsv);
}

/* prepcompare()
- create "comparison" directory
- For each student in the roster
---- prepend .c files with student lastname-first-initial
---- copy new .c files to comparison directory.  
*/
void setupcompare(){
	
	
}



/*
int main (void)
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




//Taken From: http://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
int EndsWith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

void copyFile(char* source, char *dest){
  int c;
  FILE *s, *d;
  
  s = fopen(source, "r");
  d = fopen(dest, "w");
  if(!s){
    printf("Could not open file %s\n", source);
  } else if(!d){
    printf("Could not open file %s\n", dest);
  } else {
    c = getc(s);
    while(c != EOF){
      putc(c, d);
      c = getc(s);
    }
  }
  fclose(s);
  fclose(d);
  
}

size_t max(size_t a, size_t b)
  {if(a>b) return a; return b;}

void compare_output(FILE*expFile, FILE*gotFile, size_t *total, size_t*match){
  char exp[1000001], got[1000001], *eend, *gend, eTemp[101], gTemp[101];
  int ** A;
  size_t e=0, g=0, i, j, k;
  *total = 0;
  *match = 0;
  *exp = '\0';
  eend = exp;
  *got = '\0';
  gend = got;
  while(fscanf(expFile, "%s", eTemp) > 0){
    strcpy(eend, eTemp);
    eend += strlen(eTemp);
  }
  while(fscanf(gotFile, "%s", gTemp) > 0){
    strcpy(gend, gTemp);
    gend += strlen(gTemp);
  }
  
  e = eend-exp;
  g = gend-got;
  A = (int**)calloc(sizeof(int*), e);
  for( i =0; i < e; i++)
    A[i] = calloc(sizeof(int), g);
  
  for(i = 0; i < e; i++)
    for(j = 0; j < g; j++){
      if(i== 0 || j == 0) {
        if(exp[i] == got[j])
          A[i][j] = 1;
      }else if (exp[i] == got[j]){
          A[i][j] = A[i-1][j-1] +1;
      }else {
          A[i][j] = max(A[i-1][j], A[i][j-1]);
      }
  }
  *total = max(e,g);
  *match = A[e-1][g-1];
  
  for( i =0; i < e; i++)
    free(A[i]);
  free(A);
  
}

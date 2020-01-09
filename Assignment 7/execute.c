#include "execute.h"


 int execute_command(char ** command, char * stdin_file, char* stdout_file, char* stderr_file){
  int status =0;
#ifdef __MINGW__
  int sin = _dup(0);
  int sout = _dup(1);
  int serr = _dup(2);
  FILE *out_file, *in_file, *err_file;
  //if given files for redirected IO
  if(stdin_file){
    fopen_s( &in_file, stdin_file, "r" );
    _dup2(_fileno(in_file), 0);
  }
  if(stdout_file){
    fopen_s( &out_file, stdout_file, "w" );
    _dup2(_fileno(out_file), 1);
  }
  if(stderr_file){
    fopen_s( &err_file, stderr_file, "w" );
    _dup2(_fileno(err_file), 2);
  }
  
  status = spawnvp(P_WAIT, command[0], command);
  
  //restore standard IO
  if(stdin_file){
    fclose(in_file);
    _dup2(sin, 0);
  }
  if(stdout_file){
    fclose(out_file);
    _dup2(sout, 1);
  }
  if(stderr_file){
    fclose(err_file);
    _dup2(serr, 2);
  } 
#else
  //USING FORK/EXEC 
  //first fork to run compile execution in child process;
  int pid = fork(); //0 is child, non-zero is parent with pid of child
  
  if(pid == 0){
    //child process, 
    //set redirection of standard IO
    if(stdin_file)
      freopen(stdin_file, "r",stdin);
    if(stdout_file)
      freopen(stdout_file, "w",stdout);
    if(stderr_file)
      freopen(stderr_file, "w",stderr);
    //execute compilation
    execvp(command[0], command);
    printf("Execution of %s failed\n", command[0]);
    exit(1);
  } else {
    int status;
    wait(&status); 
  }
#endif
  return status;
}
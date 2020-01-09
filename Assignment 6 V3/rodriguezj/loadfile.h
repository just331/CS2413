#ifndef ___loadfile___H___
#define ___loadfile___H___

#include<stdio.h>
#include"my_size_t.h"
#include"trackedmemory.h"

//Code Taken From Stack Overflow:
//http://stackoverflow.com/questions/7856741/how-can-i-load-a-whole-file-into-a-string-in-c


static char * loadfile(char* input_file_name){
    char *file_contents =0;
    long input_file_size;
    FILE *input_file = fopen(input_file_name, "rb");
    if(input_file){
      fseek(input_file, 0, SEEK_END);
      input_file_size = ftell(input_file);
      rewind(input_file);
      file_contents = MALLOC((input_file_size+1) * (sizeof(char)));
      fread(file_contents, sizeof(char), input_file_size, input_file);
      fclose(input_file);
      file_contents[input_file_size] = 0;
    } else 
      printf("Failed to open file: %s\n", input_file_name);
    return file_contents;
}



#endif

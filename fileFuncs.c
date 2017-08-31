#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileFuncs.h"

int fileAdd(strStruct input){

  //input[1] - m3u
  //input[2] - file

  if(input.number != 2){
    return -2;
  }

  FILE *file;
  file = fopen(input.string[1], "a");
  if(file == NULL){
    fclose(file);
    return -1;
  }

  fprintf(file, "%s\n", input.string[2]);

  fclose(file);
  return 0;
}

int fileRemove(strStruct input){

  //input[1] - m3u
  //input[2] - file

  if(input.number != 2){
    return -2;
  }
  
  int error;

  FILE *file;
  FILE *temp;
  file =fopen(input.string[1], "rw");

  if(file == NULL){
    fclose(file);
    return -1;
  }

  int length = strlen(input.string[1]);
  char *tempFileDirectory = malloc((length + 5) * sizeof(*tempFileDirectory));
  strcpy(tempFileDirectory, input.string[1]);
  strcat(tempFileDirectory, ".temp");

  temp = fopen(tempFileDirectory,  "a");
  if(temp == NULL){
    fclose(temp);
    return -1;
  }
  
  char *line = malloc(2048 * sizeof(*line));

  int length2 = strlen(input.string[2]);

  char *input2 = malloc((length2+2) * sizeof(*input2));
  strcpy(input2, input.string[2]);
  input2[length2] = '\n';
  input2[length2+1] = 0;

  while(fgets(line, 2048, file)){
    int comp = strcmp(line, input2);
    if(comp == 0){ 
      printf("Removing line: \"%s\"\n", line);
      continue;
    }
    fprintf(temp, "%s", line);
  }

  fclose(file);
  fclose(temp);
  error = remove(input.string[1]);
  if(error == -1){
    return error;
  }
  error = rename(tempFileDirectory, input.string[1]);
  if(error == -1){
    return error;
  }

  free(tempFileDirectory);
  free(line);
  free(input2);
  
  return 0;
}

int fileCopy(strStruct input){

  //input[1] old m3u file
  //input[2] new m3u flie

  if(input.number != 2){
    return -2;
  }

  int error;

  FILE *file;
  FILE *file2;
  file =fopen(input.string[1], "rw");

  if(file == NULL){
    fclose(file);
    return -1;
  }

  int length = strlen(input.string[1]);

  file2 = fopen(input.string[2],  "a");
  if(file2 == NULL){
    fclose(file2);
    return -1;
  }
  
  char *line = malloc(2048 * sizeof(*line));

  while(fgets(line, 2048, file)){
    fprintf(file2, "%s", line);
  }

  fclose(file);
  fclose(file2);

  free(line);
  return 0;
}

int fileDefaultPlaylist(strStruct input){
  //input[1] = default playlist directory

  if(input.number != 1){
    return -2;
  }
}

int fileCopyFile(strStruct input){
}

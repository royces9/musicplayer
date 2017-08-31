#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "m3ufuncs.h"
#include "m3ucopy.h"

int m3unew(strStruct input){

  //input[1] = new playlist name

  if(input.number != 1){
    return -2;
  }
  FILE *file;
  file = fopen(input.string[1], "a");
  if(file == NULL){
    return -1;
  }
  fclose(file);
  return 0;
}

int m3uload(strStruct input){

  return 0;
}

int m3usave(strStruct input){

  return 0;
}

int m3udelete(strStruct input){
  if(input.number != 1){
    return -2;
  }
  printf("Are you sure you would like to delete \"%s\"?\n", input.string[1]);
  char prompt = getchar();
  if(prompt == 'Y' || prompt == 'y'){
    int error = unlink(input.string[1]);
    if(error){
      return -1;
    }
    printf("Deleted \"%s\".\n", input.string[1]);
  }
  return 0;
}

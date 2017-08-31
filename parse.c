#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "execFuncs.h"
#include "struct.h"

int parseString(char *input){
  int error = 0;

  strStruct separatedInput = separateString(input, ' ', &error);
  if(error){
    return error;
  }
  error = charfind(separatedInput);
  if(error){
    return error;
  }

  free(separatedInput.string);
}

strStruct separateString(char *input, char delimiter, int *error){
  char *tok;
  int length = 0, delimiterCount = 0, i = 0;

  strStruct out;

  char strDelimiter[2];
  strDelimiter[0] = delimiter;
  strDelimiter[1] = '\0';

  for(length = 0; input[length]; length++){
    if(input[length] == delimiter){
      delimiterCount++;
    }
  }
  
  char *input2 = malloc((length + 2)* sizeof(*input2));
  if(input2 == NULL){
    exit(1);
  }
  strcpy(input2,input);

  //allocate double array output
  char **separatedString = malloc((delimiterCount + 2) * sizeof(*separatedString));
  if(separatedString == NULL){
    exit(1);
  }

  for(int j = 0; j < (delimiterCount + 2); j++){
    separatedString[j] = malloc(length * sizeof(**separatedString));
    if(separatedString[j] == NULL){
      exit(1);
    }
  }

  input2[length+1] = 0;

  tok = strtok(input2, strDelimiter);
  
  for(i = 0; tok != NULL; i++){
    strcpy(separatedString[i], tok);
    tok = strtok(NULL, strDelimiter);
  }

  separatedString[i-1][strlen(separatedString[i-1])] = '\0';
  strcpy(separatedString[i], "");
  free(input2);

  out.string = separatedString;
  out.number = delimiterCount;
  
  return out;
}

void errorReport(int error){
  switch(error){
  case -1: printf("File did not open cleanly."); break;
  case -2: printf("Incorrect number of inputs."); break;
  }
  printf("\n");
}

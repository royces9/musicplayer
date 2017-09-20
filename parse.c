#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_mixer.h>

#include "parse.h"
#include "execFuncs.h"
#include "struct.h"

int parseString(char *input, Mix_Music *music){
  int error = 0;

  strStruct separatedInput = separateString(input, '\'', &error);
  separatedInput.music = music;

  if(error){
    freeDoubleArray(separatedInput.string);
    return error;
  }

  error = charfind(separatedInput);

  if(error){
    freeDoubleArray(separatedInput.string);
    return error;
  }

  freeDoubleArray(separatedInput.string);
}

strStruct separateString(char *input, char delimiter, int *error){
  strStruct out;
  char strDelimiter[2];
  strDelimiter[0] = delimiter;
  strDelimiter[1] = '\0';

  int length = strlen(input);
  int i, j = 0;

  char *tok;
  for(i = 0; input[i]; i++){
    if(input[i] == delimiter){
      j++;
    }
  }

  char *input2 = malloc((length + 2) * sizeof(*input2));
  __MALLOC_CHECK(input2, *error)

  strcpy(input2, input);
  input2[length] = 0;

  tok = strtok(input2, strDelimiter);
  int strlenTok = strlen(tok);

  if(tok[strlenTok-1] == ' '){
    tok[strlenTok-1] = '\0';
  }

  //allocate double array and populate it with strings
  out.string = malloc(((j/2) + 3) * sizeof(out.string[0]));
  __MALLOC_CHECK(out.string, *error);

  out.string[0] = malloc((strlenTok + 1) * sizeof(out.string[0][0]));
  __MALLOC_CHECK(out.string[0], *error);


  strcpy(out.string[0], tok);
  tok = strtok(NULL, strDelimiter);

  for(i = 1; tok != NULL; i++){
    if(tok[0] == ' '){ //ignore the spaces inbetween each argument
      i--;
      tok = strtok(NULL, strDelimiter);
      continue;
    }
    out.string[i] = malloc((strlen(tok) + 1) * sizeof(out.string[0][0]));
    __MALLOC_CHECK(out.string[i], *error);
    strcpy(out.string[i], tok);
    tok = strtok(NULL, strDelimiter);
  }


  out.string[i] = malloc(sizeof(out.string[0][0])); //allocate an end string that is just a char
  //  __MALLOC_CHECK(out.string[i], *error);
  out.string[i][0]= '\0'; //end string

  free(input2);

  out.number = --i;

  return out;
}

void freeDoubleArray(char **input){
  int i = 0;
  for(i = 0; strcmp(input[i], ""); i++){
    free(input[i]);
  }
  free(input[i]);
  free(input);
}

void errorReport(int error){
  switch(error){
  case -1: printf("File did not open cleanly."); break;
  case -2: printf("Incorrect number of inputs."); break;
  case -3: printf("Audio errors."); break;
  case -4: printf("File does not exist."); break;
  case -5: printf("Volume not set."); break;
  case -6: printf("Malloc error."); break;
  case -7: printf("Pthread error."); break;
  }
  printf("\n");
}

int startUp(){
  if(Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG) == -1){
    printf("Mix_Init: %s\n", Mix_GetError());
    return -3;
  }

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    return -3;
  }
}

void cleanUp(Mix_Music *music){
  Mix_CloseAudio();
}

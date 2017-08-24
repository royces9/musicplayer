#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

#define NF = 10

static const char FUNCTIONS[NF][20]{
}

enum functionEnums{
}

int funcfind(char buffer[]){
  for(int i = 0; i < NF; i++){
    if(!strcmp(FUNCTIONS[i], buffer)){
      return i;
    }
  }
  return NF;
}

int charfind(char buffer[]){
  int funcNumber = funcfind(buffer), error = 0;

  switch(funcNumber){
  }
}

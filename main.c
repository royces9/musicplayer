#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "parse.h"

int main(){
  char *input;
  int error;

  while(error <= 0){
    input = readline(">>");
    add_history(input);

    if(*input == 0){
      continue;
    }

    else{
      error = parseString(input);
    }

    if(error != 0){
      errorReport(error);
    }
  }

  return 0;
}

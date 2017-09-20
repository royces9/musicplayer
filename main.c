#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include <SDL/SDL_mixer.h>

#include "struct.h"
#include "playList.h"
#include "parse.h"

Mix_Music *global_music;

int main(){
  char *input;
  int error = 0;

  error = startUp();
  Mix_HookMusicFinished(changePlaying);
  //  play_list(global_music);

  while(error <= 0){
    input = readline(">>");
    add_history(input);
    if(*input == 0){
      continue;
    }

    else{
      error = parseString(input, global_music);
    }

    if(error < 0){
      errorReport(error);
    }

    free(input);
  }

  cleanUp(global_music);

  return 0;
}

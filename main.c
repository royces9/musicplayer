#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include <SDL/SDL_mixer.h>

#include "screen.h"
#include "struct.h"
#include "playList.h"
#include "parse.h"

Mix_Music *global_music;

int main(){

  //ncurses initialization
  initializeNcurses();
  makeScreen();

  //  char input[2048];

  int error = 0;
  
  error = startUp();
  Mix_HookMusicFinished(changePlaying);
  //  play_list(global_music);

  char *input = malloc(2048 * sizeof(input));

  while(error <= 0){
    memset(input, 0, 2048);
    inputHandling(input);

     if(*input == 0){
      continue;
    }

    else{
      error = parseString(input, global_music);
    }

    if(error < 0){
      errorReport(error);
    }


  }

  free(input);
  cleanUp(global_music);

  endwin();
  return 0;
}

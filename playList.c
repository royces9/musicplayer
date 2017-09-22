#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parse.h"
#include "playList.h"

int _firstRunFlag = 0;

void changePlaying(){
  strcpy(_currentSong, _playlistArray[_playlistCount++]); //sets the next file to _playlistArray[_playlistCount]
  __PLAY_GLOBAL_MUSIC(); //defined in playList.h 
  printf("Now playing \"%s\".\n", _currentSong);
}

int createPlaylistArray(){
  if(_firstRunFlag){ //so the array is free'd everytime a new array is created, firstRun is so there's no free the first time
    freeDoubleArray(_playlistArray);
    _firstRunFlag = 1;
  }

  FILE *playlist = fopen(_currentPlaylist, "r");
  if(playlist == NULL){
    return -1;
  }

  int error;
  int listShuffle[_lineCount]; //an array with a number from 0 to the number of files

  for(int i = 0; i < _lineCount; i++){
    listShuffle[i] = i;
  }

  if(_lineCount > 1){
    size_t i;
    for(i = 0; i < _lineCount-1; i++){
      size_t j = i + rand() / (RAND_MAX / (_lineCount - i) + 1);
      int t = listShuffle[j];
      listShuffle[j] = listShuffle[i];
      listShuffle[i] = t;
    }
  } //shuffles the numbers around

  _playlistArray = malloc(_lineCount * sizeof(*_playlistArray));
  __MALLOC_CHECK(_playlistArray, error);

  for(int i = 0; i < _lineCount; i++){
    char temp[4096];
    fgets(temp, 4098, playlist);
    int strlenTemp = strlen(temp)+1;
    _playlistArray[listShuffle[i]] = malloc(strlenTemp * sizeof(**_playlistArray));
    __MALLOC_CHECK(_playlistArray[listShuffle[i]], error); 

    strcpy(_playlistArray[listShuffle[i]], temp); //maps the listShuffle index "i" to _playlistArray index "listShuffle[i]"
    *(_playlistArray[listShuffle[i]]+strlenTemp-2) = '\0'; //remove new line
  }
  _firstRunFlag = 1;
  return 0;
}

int searchArray(char *search, char **array, int length){
  for(int i = 0; i < length; i++){
    if(!strcmp(array[i], search)){
      return i;
    }
  }
}

#include <ncurses.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "screen.h"
#include "playlistFuncs.h"
#include "playList.h"

int newPlaylist(strStruct input){
  //input[1] = new playlist name
  if(input.number != 1){
    return -2;
  }

  if(access(input.string[1], F_OK) != -1){
    wprintw(topright, "Playlist \"%s\" already exists.\n", input.string[1]);
    return 0;
  }

  FILE *file;
  file = fopen(input.string[1], "a");
  if(file == NULL){
    return -1;
  }
  fclose(file);

  wprintw(topright, "New playlist \"%s\" created.\n", input.string[1]);
  return 0;
}

int updatePlaylist(strStruct input){ //reloads the playlist array
  if(input.number != 1){
    return -2;
  }
    
  if(!strcmp(input.string[1], _currentPlaylist)){
    wprintw(topright, "Playlist does not need to be updated.\n");
    return 0;
  }

  createPlaylistArray();
  return 0;
}

int savePlaylist(strStruct input){
  return 0;
}

int deletePlaylist(strStruct input){
  if(input.number != 1){
    return -2;
  }
  if(access(input.string[1], F_OK) == -1){
    wprintw(topright, "Are you sure you would like to delete \"%s\"?\n", input.string[1]);
    char prompt = getchar();
    if(prompt == 'Y' || prompt == 'y'){
      int error = unlink(input.string[1]);
      if(error){
	return -1;
      }
      wprintw(topright, "Deleted \"%s\".\n", input.string[1]);
    }
  }
  else{
    wprintw(topright, "File \"%s\" does not exist.\n", input.string[1]);
  }
  return 0;
}

int playPlaylist(strStruct input){
  //input[1] playlist name
  //input[2] song name
  //input[3] play mode

  if(input.number != 3){
    return -2;
  }

  time_t t;
  srand((unsigned) time(&t)); //seed for the prng

  if(access(input.string[1], F_OK) != -1){ //check file existence
    strcpy(_currentPlaylist, input.string[1]); //set current playlist

    FILE *playlist = fopen(_currentPlaylist, "r");
    if(playlist == NULL){
      return -1;
    }

    _lineCount = 0; //line count of the file
    while(!feof(playlist)){
      char ch = fgetc(playlist);
      if(ch == '\n'){
	_lineCount++;
      }
    }
    fclose(playlist);

    createPlaylistArray(); //create array holding every line of the file

    if(!strcmp(input.string[2], "#none")){ //check to play a random song
      strcpy(_currentSong, _playlistArray[0]); //sets the first song to 0
      _playlistCount = 1; //sets the count to play index 1 next

      __PLAY_GLOBAL_MUSIC();
    }
    else{ //plays the selected song from input.string[2]
      if(access(input.string[2], F_OK) != -1){ //file exists
	strcpy(_currentSong, input.string[2]);

	__PLAY_GLOBAL_MUSIC();

	_playlistCount = searchArray(_currentSong, _playlistArray, _lineCount)+1;
      }
      else{ //if the file doesn't exist picks a random one
	wprintw(topright, "File \"%s\"does not exist.\n", input.string[2]);
	strcpy(_currentSong, _playlistArray[0]);
	_playlistCount = 1;

	__PLAY_GLOBAL_MUSIC();
      }
    }
    wprintw(topright, "Now playing \"%s\".\n", _currentSong);
    return 0;
  }
  wprintw(topright, "File \"%s\" does not exist.\n", input.string[1]);
  return -4;
}

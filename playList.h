#ifndef PLAY
#define PLAY

#include "struct.h"

#define __PLAY_GLOBAL_MUSIC()\
  global_music = Mix_LoadMUS(_currentSong);\
  if(global_music == NULL){\
    printf("%s\n", Mix_GetError());		\
  }\
  Mix_PlayMusic(global_music, 1);

extern Mix_Music *global_music; //global Mix_Music struct from main.c

enum{
  singleFile,
  shuffle,
  inOrder
} playMode;

int _lineCount; //keeps track of how many lines a file is
int _playlistCount; //keeps track of where in the array we are.

char _currentPlaylist[4096];
char _currentSong[4096];
char **_playlistArray;

void changePlaying();
int createPlaylistArray();
int searchArray(char *search, char **array,int length);
//int currentlyPlaying(strStruct input);

#endif //PLAY

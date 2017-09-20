#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <locale.h>
#include <wchar.h>

#include "parse.h"
#include "playList.h"

unsigned int _currentPlaylist[4096];
unsigned int _currentSong[4096];
unsigned int **playlistArray;

extern Mix_Music *global_music;

int _lineCount;
int playlistCount;
enum {
  singleFile,
  inOrder,
  shuffle
} playMode;

void changePlaying(){
unsigned int output[4096];
  pickNextFile();
  global_music = Mix_LoadMUS(_currentSong);
  if(global_music == NULL){
    printf("%s\n", Mix_GetError());
  }
  Mix_PlayMusic(global_music, 1);
}

int pickNextFile(){
  FILE *playlist;

  playlist = fopen(_currentPlaylist, "r");
  if(playlist == NULL){
    return -1;
  }
  else{
    strcpy(_currentSong, playlistArray[playlistCount]);
    removeNewLine(_currentSong);
    playlistCount++;
  }
  fclose(playlist);
  return 0;
}

void removeNewLine(unsigned int *input){
  //  char buffer[4096];
  //  wcstombs(buffer, input, sizeof(buffer));
  //  printf("%s\n", buffer);
  printf("%d\n", sizeof(unsigned int));
  for(int i = 0;input[i]; i++){
    printf("hex %08x\n", input[i]);
    int temp = input[i];
    short b1 = input[i] & 0xFF;
    short b2 = input[i]>>8 & 0xFF;
    short b3 = input[i]>>16 & 0xFF;
    short b4 = input[i]>>24 & 0xFF;

    if(b1 == 0x0A){
      input[i] = temp & 0xFFFFFF00;
      printf("hexA %08x\n", input[i]);
      break;
    }
    else if(b2 == 0x0A){
      input[i] = temp & 0xFFFF00FF;
      printf("hexB %08x\n", input[i]);
      break;
    }
    else if(b3 == 0x0A){
      input[i] = temp & 0xFF00FFFF;
      printf("hexC %08x\n", input[i]);
      break;
    }
    else if(b4 == 0x0A){
      input[i] = temp & 0x00FFFFFF;
      printf("hexD %08x\n", input[i]);
      break;
    }
  }
}

int createPlaylistArray(){
  FILE *playlist = fopen(_currentPlaylist, "r");
  int error;
  int listShuffle[_lineCount];
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
  }
  playlistArray = malloc(_lineCount * sizeof(*playlistArray));
  __MALLOC_CHECK(playlistArray, error);

  for(int i = 0; i < _lineCount; i++){
    unsigned int temp[4096];
    fgets(temp, 4098, playlist);
    temp[strlen(temp)-1]=0;
    playlistArray[listShuffle[i]] = malloc((strlen(temp) + 2) * sizeof(**playlistArray));
    __MALLOC_CHECK(playlistArray[listShuffle[i]], error);

    strcpy(playlistArray[listShuffle[i]], temp);
  }
  return 0;
}

int currentlyPlaying(strStruct input){
  if(access(input.string[1], F_OK) != -1){
    strcpy(_currentPlaylist, input.string[1]);
    FILE *playlist = fopen(_currentPlaylist, "r");
    if(playlist == NULL){
      return -1;
    }

    unsigned int temp[4096];
    fgets(temp, 4096, playlist);
    strcpy(_currentSong, temp);
    removeNewLine(_currentSong);

    printf("%s\n", _currentSong);
    printf("%ls\n", _currentSong);
    printf("%d\n", strlen(_currentSong));

    printf("test-1\n");
    setlocale(LC_CTYPE, "ja_JP.UTF-8");
    char buffer[4096];
    wcstombs(buffer, _currentSong, sizeof(buffer));
    global_music = Mix_LoadMUS(buffer);
    printf("test\n");
    if(!global_music){
      printf("%s\n", Mix_GetError());
      return -3;
    }

    Mix_PlayMusic(global_music, 1);

    _lineCount = 0;
    while(!feof(playlist)){
      unsigned int ch = fgetc(playlist);
      if(ch == '\n'){
	_lineCount++;
      }
    }
    fclose(playlist);
    return createPlaylistArray();
  }
  return -4;
}

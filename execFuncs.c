#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_mixer.h>

#include "execFuncs.h"
#include "musicFuncs.h"
#include "fileFuncs.h"
#include "musicFuncs.h"
#include "playlistFuncs.h"

#define NF 19

const char FUNCTIONS[NF][20]={
  "-play",
  "-pause",
  "-play-pause",
  "-seek",
  "-absolute-seek",
  "-volume",
  "-absolute-volume",
  "-mute",

  "-new",
  "-load",
  "-save",
  "-delete",
  "-play-list",

  "-add",
  "-remove",
  "-copy",
  "-default-playlist",
  "-copy-file",

  "-quit"
};

enum functionEnums{
  ePlay,
  ePause,
  ePlayPause,
  eSeek,
  eAbsoluteSeek,
  eVolume,
  eAbsoluteVolume,
  eMute,

  eNew,
  eLoad,
  eSave,
  eDelete,
  ePlayPlaylist,

  eAdd,
  eRemove,
  eCopy,
  eDefaultPlaylist,
  eCopyFile,

  eQuit
};

int funcfind(char buffer[]){
  for(int i = 0; i < NF; i++){
    if(!strcmp(FUNCTIONS[i], buffer)){
      return i;
    }
  }
  return NF;
}

int charfind(strStruct input){
  int funcNumber = funcfind(input.string[0]), error = 0;

  //input[0] - function name // input[1] - arg1 // input[2] - arg2 // etc

  switch(funcNumber){
  case ePlay:
    return playMusic(input);

  case ePause:
    return pauseMusic(input);

  case ePlayPause:
    return playPauseMusic(input);
    
  case eSeek:
    return seekMusic(input);
    
  case eAbsoluteSeek:
    return absoluteSeekMusic(input);
    
  case eVolume:
    return volumeMusic(input);
    
  case eAbsoluteVolume:
    return absoluteVolumeMusic(input);
    
  case eMute:
    return muteMusic(input);

  case eNew:
    return newPlaylist(input);

  case eLoad:
    return loadPlaylist(input);

  case eSave:
    return savePlaylist(input);

  case eDelete:
    return deletePlaylist(input);

  case ePlayPlaylist:
    return playPlaylist(input);

    break;

  case eAdd:
    return fileAdd(input);

  case eRemove:
    return fileRemove(input);

  case eCopy:
    return fileCopy(input);

  case eDefaultPlaylist:
    return fileDefaultPlaylist(input);

  case eCopyFile:
    return fileCopyFile(input);

  case eQuit:
    return 1;

  default:
    printf("Invalid command.\n");
    return 0;
  }
}

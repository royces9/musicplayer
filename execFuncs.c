#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "m3ufuncs.h"
#include "fileFuncs.h"

#define NF 18

const char FUNCTIONS[NF][20]={
  "-play",
  "-pause",
  "-play-pause",
  "-seek",
  "-absolute-seek",
  "-volume",
  "-mute",

  "-new",
  "-load",
  "-save",
  "-delete",

  "-add",
  "-remove",
  "-copy",
  "-default-playlist",
  "-copy-file",
  "-playlist",
    "quit"
};

enum functionEnums{
  ePlay,
  ePause,
  ePlayPause,
  eSeek,
  eAbsoluteSeek,
  eVolume,
  eMute,

  eNew,
  eLoad,
  eSave,
  eDelete,

  eAdd,
  eRemove,
  eCopy,
  eDefaultPlaylist,
  eCopyFile,
  ePlaylist,
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
    break;
  case ePause:
    break;
  case ePlayPause:
    break;
  case eSeek:
    break;
  case eAbsoluteSeek:
    break;
  case eVolume:
    break;
  case eMute:
    break;

  case eNew:
    return m3unew(input);
    break;
  case eLoad:
    return m3uload(input);
    break;
  case eSave:
    return m3usave(input);
    break;
  case eDelete:
    return m3udelete(input);
    break;

  case eAdd:
    return fileAdd(input);
    break;
  case eRemove:
    return fileRemove(input);
    break;
  case eCopy:
    return fileCopy(input);
    break;
  case eDefaultPlaylist:
    return fileDefaultPlaylist(input);
    break;
  case eCopyFile:
    return fileCopyFile(input);
    break;
  case ePlaylist:

    break;

  case eQuit:
    return 1;
  default:
    printf("Invalid command.\n");
    return 0;
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "playlistFuncs.h"
#include "playList.h"

int newPlaylist(strStruct input){

  //input[1] = new playlist name

  if(input.number != 1){
    return -2;
  }

  if(access(input.string[1], F_OK) != -1){
    printf("Playlist \"%s\" already exists.\n", input.string[1]);
    return 0;
  }

  FILE *file;
  file = fopen(input.string[1], "a");
  if(file == NULL){
    return -1;
  }
  fclose(file);

  printf("New playlist \"%s\" created.\n", input.string[1]);

  return 0;
}

int loadPlaylist(strStruct input){
  return 0;
}

int savePlaylist(strStruct input){
  return 0;
}

int deletePlaylist(strStruct input){
  if(input.number != 1){
    return -2;
  }
  printf("Are you sure you would like to delete \"%s\"?\n", input.string[1]);
  char prompt = getchar();
  if(prompt == 'Y' || prompt == 'y'){
    int error = unlink(input.string[1]);
    if(error){
      return -1;
    }
    printf("Deleted \"%s\".\n", input.string[1]);
  }
  return 0;
}

int playPlaylist(strStruct input){
  //input[1] playlist name
  //input[2] play mode
  if(input.number != 2){
    return -2;
  }

  return currentlyPlaying(input);
}

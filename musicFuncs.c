#include <SDL/SDL_mixer.h>
#include "musicFuncs.h"

int playMusic(strStruct input){
  //input[1] = file name
  if(input.number != 1){
    return -2;
  }

  input.music = Mix_LoadMUS(input.string[1]);
  if(!input.music){
    return -4;
  }
  Mix_PlayMusic(input.music, 1);
  return 0;
}

int pauseMusic(strStruct input){
  if(Mix_PausedMusic()){
    printw("Music not playing.\n");
    return 0;
  }
  Mix_PauseMusic();
  return 0;
}

int playPauseMusic(strStruct input){
  if(Mix_PausedMusic()){
    Mix_ResumeMusic();
  }
  else{
    pauseMusic(input);
  }
  return 0;
}

int seekMusic(strStruct input){
  return 0;
}

int absoluteSeekMusic(strStruct input){
  return 0;
}

int volumeMusic(strStruct input){
  if(input.number != 1){
    return -2;
  }

  int volumeChange = atoi(input.string[1]);
  int currVolume =  Mix_VolumeMusic(-1);

  int newVolume = volumeChange + currVolume;
  if(newVolume < 0){
    newVolume = 0;
  }

  Mix_VolumeMusic(newVolume);
  return 0;
}

int absoluteVolumeMusic(strStruct input){
  if(input.number != 1){
    return -2;
  }

  int volume = atoi(input.string[1]);
  if(volume < 0){
    volume = 0;
  }

  Mix_VolumeMusic(volume);
  
  return 0;
}

int muteMusic(strStruct input){
  Mix_VolumeMusic(0);
  return 0;
}

#ifndef PLAY
#define PLAY

#include "struct.h"

void changePlaying();
int pickNextFile();
void removeNewLine(unsigned int *input);
int createPlaylistArray();
int currentlyPlaying(strStruct input);

#endif //PLAY

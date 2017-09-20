#ifndef PARSE
#define PARSE

#include <SDL/SDL_mixer.h>
#include "struct.h"

#define __MALLOC_CHECK(pointer, error) \
  if(pointer == NULL){\
  error = -6; \
  }

int parseString(char *input, Mix_Music *music);
strStruct separateString(char *input, char delimiter, int *error);
void freeDoubleArray(char **input);
void errorReport(int error);
int startUp();
void cleanUp(Mix_Music *music);

#endif //PARSE

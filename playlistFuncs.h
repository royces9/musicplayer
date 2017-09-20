#ifndef M3UFUNCS
#define M3UFUNCS

#include "struct.h"

int _LOADED_LISTS;
int _MAX_LOAD;

int newPlaylist(strStruct input);
int loadPlaylist(strStruct input);
int savePlaylist(strStruct input);
int deletePlaylist(strStruct input);
int playPlaylist(strStruct input);

#endif //M3UFUNCS

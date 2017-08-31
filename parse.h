#ifndef PARSE
#define PARSE

#include "struct.h"

int parseString(char *input);
strStruct separateString(char *input, char delimiter, int *error);
void errorReport(int error);

#endif //PARSE

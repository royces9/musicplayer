#ifndef NCURSE
#define NCURSE

int _maxx, _maxy, _halfx, _halfy;
WINDOW *topleft, *topright, *bottom;

void initializeNcurses();
void makeScreen();

#endif //NCURSE

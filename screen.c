#include <ncurses.h>

#include "screen.h"

void initializeNcurses(){
  initscr();
  raw();
  noecho();
  wmove(topright, 0, 0);
  keypad(topleft, TRUE);
}

void makeScreen(){
  getmaxyx(stdscr, _maxy, _maxx);
  _halfx = _maxx / 2;
  _halfy = _maxy /2;

  topleft = newwin(_halfy/3, _halfx, 0, 0);
  topright = newwin(_halfy/3, _halfx, 0, _halfx);
  bottom = newwin(_halfy*5/3, _maxx, _halfy/3, 0);

  box(topleft, 0, 0);
  box(topright, 0, 0);
  box(bottom, 0, 0);
  wrefresh(topleft);
  wrefresh(topright);
  wrefresh(bottom);
}

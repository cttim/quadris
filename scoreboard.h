#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__
#include <iostream>
#include "grid.h"

class scoreboard{
  int highscore;
  int score;
  int level;
  grid* g;
  char next;
  void update();
 public:
  scoreboard();
  ~scoreboard();
  void setnext(char);//call in driver
  void connectgrid(grid*);//call in driver
  void printscore();
};
#endif

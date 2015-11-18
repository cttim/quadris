#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <string>
#include "cell.h"
#include "block.h"
#include "window.h"
class grid{
  Cell **thegrid;
  Block* b;
  Block* nb;
  bool gg;
  int rsize,csize;
  int level;
int score;
int highscore;
//scoreboard* board;
 Xwindow* w;
 public:
  grid();
  ~grid();
  void turnon(int,int);
  void turnoff(int,int);
  void initblock(char);
  void initnextblock(char);
  void changeblock();
  void cleargrid();
  void clear();
  void clearline(int );
  void init();
  void setlevel(int);
  void rotate();
  void drop();//remember to delete b
int getlevel();
int gethighscore();
int getscore();
 int getrsize();
 int getcsize();
 //friend std::ostream& ::operator<<(std::ostream &out,const grid &g);
 void printgrid();
 void shiftr();
 void shiftl();
 void shiftd();
 void gameover();
 void sethighscore(int);
 char getnext();
 bool getgg();
 void setwindownull();
};
#endif

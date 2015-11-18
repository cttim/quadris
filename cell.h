#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
//#include "textdisplay.h"
#include "window.h"

class Cell{
 private:
  char type;
  int level;
  int r, c,x,y,width,height;
  bool isalive;
int alivenum;
int numneighbour;
Cell *neighbours[3];
 Xwindow *w;
 public:
  Cell();
  ~Cell();
  void setlevel(int);
  void setliving();    
  void setdead();     
  void setcoords(int r, int c, int x,int y,int width,int height, Xwindow *w);
  void setcelltype(char);
  char gettype();
  int getlevel();
  bool getstatus();
void addneighbour(Cell *neighbour);
void notifyneighbour();
void notify();
int getalivenum();
 void draw();
 void undraw();
};

#endif

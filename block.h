//Aaron last edit:15
//do not touch this-Aaron

#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>

class Block{
  
  
  //void clearBlock();//do not need,all fields are in stack

  //singleton start here
  static Block*bi;
  static Block*bj;
  static Block*bl;
  static Block*bo;
  static Block*bs;
  static Block*bz;
  static Block*bt;
  int x[4],y[4];
  int oldx[4],oldy[4];
  int oz[2];
  char type;
  int rot;//rotate state,can be 0,1,2,3,according to clockwise
  int level;
  Block(char);//this one is mine. do not call this in grid,use get
  void findoz();
  void r(int);
  
 public:
  //Block();//do not actually need
  ~Block();
  
  //function that can change fields:
  void rotate();
  //void CheckClear();//call ClearLine and pass in line num
  void shiftleft();
  void shiftright();
  void shiftdown();
  void stepback();
  void ChangeLevel(int);
//getter
  int gettype();
  int getlevel();
  int getx(int);
  int gety(int);
  void reset();
  
  
  //get singleton field
  static Block* geti();
  static Block* getj();
  static Block* getl();
  static Block* geto();
  static Block* gets();
  static Block* getz();
  static Block* gett();
  //char gettype();
  //int getrot();
  void testprint();//for debug propose
};

#endif

//do not touch this-Aaron
#include "cell.h"
using namespace std;
Cell::Cell(){
  isalive=false;
  r=-1;c=-1;
  type=' ';
  level=0;
  isalive=false;
  alivenum=3;
  numneighbour=0;
  // cout<<18<<endl;
  for (int i=0;i<3;i++){
    neighbours[i]=NULL;
  }
}
Cell::~Cell(){}

void Cell::setlevel(int l){
  level=l;
}

void Cell::setliving(){
  isalive=true;
}

void Cell::setdead(){
  isalive=false;
}

void Cell::setcoords(int r,int c,int x,int y,int width,int height,Xwindow *w){
  this->r=r;
  this->c=c;
  this->x=x;
  this->y=y;
  this->width=width;
  this->height=height;
  this->w=w;
}

void Cell::setcelltype(char c){
  type=c;
}

char Cell::gettype(){
  return type;
}

int Cell::getlevel(){
  return level;
}

bool Cell::getstatus(){
  return isalive;
}

void Cell::addneighbour(Cell *neighbour){
  //cout<<"add"<<endl;
  neighbours[numneighbour]=neighbour;
  numneighbour++;
  //cout<<numneighbour<<endl;
}

void Cell::notifyneighbour(){
  //cout<<"notify"<<endl;
  for (int i=0;i<numneighbour;i++){
    if (neighbours[i]!=NULL){
      neighbours[i]->notify();
      //cout<<"notify"<<endl;
    }
  }
}

void Cell::notify(){
  alivenum=alivenum-1;
  //cout<<alivenum<<endl;
}

int Cell::getalivenum(){
  return alivenum;
}

void Cell::draw(){
  /*cout<<type<<endl;*/
  if (type=='I'){
    //cout<<"i color"<<endl;
    w->fillRectangle(x,y,width,height,2);
  }
  else if (type=='J'){
    // cout<<"j color"<<endl;
    w->fillRectangle(x,y,width,height,3);
  }
  else if (type=='S'){
    w->fillRectangle(x,y,width,height,4);
  }
  else if (type=='L'){
    w->fillRectangle(x,y,width,height,5);
  }
  else if (type=='O'){
    w->fillRectangle(x,y,width,height,6);
  }
  else if (type=='T'){
    w->fillRectangle(x,y,width,height,7);
  }
  else {
    w->fillRectangle(x,y,width,height,8);
  }
  w->fillRectangle(x,y,width,1,0);
  w->fillRectangle(x,y,1,height,0);
w->fillRectangle(x+20,y,1,height,0);
w->fillRectangle(x,y+20,width,1,0);
}

void Cell::undraw(){
  w->fillRectangle(x,y,width,height,0);
w->fillRectangle(x+20,y,1,height,0);
w->fillRectangle(x,y+20,width,1,0);
}

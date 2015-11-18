//Aaron last edit:15
//do not touch this-Aaron
#include <iostream>
#include "block.h"
using namespace std;

Block* Block::bi= 0;
Block* Block::bj= 0;
Block* Block::bl= 0;
Block* Block::bo= 0;
Block* Block::bs= 0;
Block* Block::bz= 0;
Block* Block::bt= 0;

Block::~Block(){
}

void Block::reset(){//do I have to do this?
  switch (type){
  case 'I':
    x[0]=0;x[1]=1;x[2]=2;x[3]=3;
    y[0]=y[1]=y[2]=y[3]=3;
    break;
  case 'J':
    x[0]=0;y[0]=3;
    x[1]=0;x[2]=1;x[3]=2;
    y[1]=y[2]=y[3]=4;
    break;
  case 'L':
    x[0]=2;y[0]=3;
    y[1]=y[2]=y[3]=4;
    x[1]=0;x[2]=1;x[3]=2;
    break;
  case 'O':
    x[0]=0;y[0]=3;
    x[1]=1;y[1]=3;
    x[2]=0;y[2]=4;
    x[3]=1;y[3]=4;
    break;
  case 'S':
    x[0]=1;y[0]=3;
    x[1]=2;y[1]=3;
    x[2]=0;y[2]=4;
    x[3]=1;y[3]=4;
    break;
  case 'Z':
    x[0]=0;y[0]=3;
    x[1]=1;y[1]=3;
    x[2]=1;y[2]=4;
    x[3]=2;y[3]=4;
    break;
  case 'T':
    x[0]=0;y[0]=3;
    x[1]=1;y[1]=3;
    x[2]=2;y[2]=3;
    x[3]=1;y[3]=4;
    break;
  }
}

//singleton init start here

Block* Block::geti(){
  if(bi){delete bi;}
  bi=new Block('I');
  return bi;
}

Block* Block::getj(){
  if(bj){delete bj;}
  bj=new Block('J');
  return bj;
}

Block* Block::getl(){
  if(bl){delete bl;}
  bl=new Block('L');
  return bl;
}

Block* Block::geto(){
  if(bo){delete bo;}
  bo=new Block('O');
  return bo;
}

Block* Block::gets(){
  if(bs){delete bs;}
  bs=new Block('S');
  return bs;
}

Block* Block::getz(){
  if(bz){delete bz;}
  bz=new Block('Z');
  return bz;
}

Block* Block::gett(){
  if(bt){delete bt;}
  bt=new Block('T');
  return bt;
}

Block::Block(char c){
  rot=0;
  level=-1;
  type=c;
  if (c=='I'){
    type='I';
    x[0]=0;x[1]=1;x[2]=2;x[3]=3;
    y[0]=y[1]=y[2]=y[3]=3;
  }
  else if (c=='J'){
    type='J';
    x[0]=0;y[0]=3;
    x[1]=0;x[2]=1;x[3]=2;
    y[1]=y[2]=y[3]=4;
  }
  else if(c=='L'){
    type='L';
    x[0]=2;y[0]=3;
    y[1]=y[2]=y[3]=4;
    x[1]=0;x[2]=1;x[3]=2;
  }
  else if(c=='O'){
    type='O';
    x[0]=0;y[0]=3;
    x[1]=1;y[1]=3;
    x[2]=0;y[2]=4;
    x[3]=1;y[3]=4;
  }
  else if(c=='S'){
    type='S';
    x[0]=1;y[0]=3;
    x[1]=2;y[1]=3;
    x[2]=0;y[2]=4;
    x[3]=1;y[3]=4;
  }
  else if(c=='Z'){
    type='Z';
    x[0]=0;y[0]=3;
    x[1]=1;y[1]=3;
    x[2]=1;y[2]=4;
    x[3]=2;y[3]=4;
  }
  else if(c=='T'){
    type='T';
    x[0]=0;y[0]=3;
    x[1]=1;y[1]=3;
    x[2]=2;y[2]=3;
    x[3]=1;y[3]=4;
  }
}

//helper function:findoz
//object: find relative (0,1) point(rotate around point) 
//and store in oz
void Block::findoz(){
  oz[0]=x[0];
  oz[1]=y[0];
  for(int i=0;i<4;i++){
    if (x[i]<oz[0]){oz[0]=x[i];}
    if (y[i]>oz[1]){oz[1]=y[i];}
    //cout<<oz[0]<<oz[1]<<'\n';
  }
}

//helper function:r
//return the rotate coords for block expect o,i blocks
//s means shift up blocks
void Block::r(int s){
  for(int i=0;i<4;i++){
    x[i]-=oz[0];
    y[i]-=oz[1];
    int xnew=x[i]*0-y[i]*1;
    int ynew=x[i]*1+y[i]*0;
    x[i]=xnew+oz[0];
    //x[i]=x[i]-1;
    y[i]=ynew+oz[1];
    y[i]=y[i]-s;
  }
}

void Block::rotate(){
  cout<<"before:"<<rot<<endl;
  for (int i=0;i<4;i++){
    oldx[i]=x[i];
    oldy[i]=y[i];
  }
  if (type=='O'){return;}
  if (type=='I'){
    if (rot==1||rot==3){
      findoz();
      y[0]=y[1]=y[2]=y[3]=oz[1];
      x[0]=oz[0];
      x[1]=oz[0]+1;
      x[2]=oz[0]+2;
      x[3]=oz[0]+3;
    }
    else if (rot==0||rot==2){
      findoz();
      x[0]=x[1]=x[2]=x[3]=oz[0];
      y[0]=oz[1];
      y[1]=oz[1]-1;
      y[2]=oz[1]-2;
      y[3]=oz[1]-3;
    }
    if (rot==3){rot=-1;}
    rot++;
    return;
  }
  if (rot==0){
    findoz();
    r(2);
  }
  else if (rot==1){
    findoz();
    r(1);
  }
  else if (rot==2){
    findoz();
    r(2);
  }
  else {//rot==3 case
    findoz();
    r(1);
  }
  if (rot==3){rot=-1;}
  rot++;
  cout<<"rot:"<<rot<<endl;
}

void Block::shiftleft(){
  for (int i=0;i<4;i++){
    oldx[i]=x[i];
    oldy[i]=y[i];
  }
  for(int i=0;i<4;i++){
    x[i]=x[i]-1;
  }
}

void Block::shiftright(){
  for (int i=0;i<4;i++){
    oldx[i]=x[i];
    oldy[i]=y[i];
  }
  for (int i=0;i<4;i++){
    x[i]=x[i]+1;
  }
}

void Block::shiftdown(){
  for (int i=0;i<4;i++){
    oldx[i]=x[i];
    oldy[i]=y[i];
  }
  for (int i=0;i<4;i++){
    y[i]=y[i]+1;
  }
}

void Block::stepback(){
  for (int i=0;i<4;i++){
    x[i]=oldx[i];
    y[i]=oldy[i];
  }
}

void Block::ChangeLevel(int a){
  level=a;
}

int Block::gettype(){
  return type;
}

int Block::getlevel(){
  return level;
}

int Block::getx(int a){
  if (a>4){return -100;}
  else {return x[a];}
}

int Block::gety(int a){
  if (a>4){return -100;}
  else {return y[a];}
}

void Block::testprint(){
  for (int i=0;i<4;i++){
    cout<<"x"<<i+1<<" "<<x[i]<<'\n';
    cout<<"y"<<i+1<<" "<<y[i]<<'\n';
  }
}

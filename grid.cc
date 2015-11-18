#include <iostream>
#include <sstream>
#include <string>
#include "grid.h"
#include "block.h"
using namespace std;

grid::grid():rsize(0),csize(0),score(0),level(0),gg(false){
  w=new Xwindow(200,430);
}

grid::~grid(){
  cleargrid();
}

void grid::init(){
  if (rsize!=0){
    cleargrid();
  }
  //level=0;
  //score=0;
  //highscore=0;
  rsize=18;
  csize=10;
  thegrid=new Cell*[rsize];
  for(int i=0;i<rsize;i++){
    thegrid[i]=new Cell[csize];
  }
  for(int i=0;i<rsize;i++){
    for(int j=0;j<csize;j++){
      thegrid[i][j]=Cell();
      thegrid[i][j].setcoords(i,j,j*20,i*20,20,20,w);
    }
  }
  if (w!=NULL){
 w->drawString(0,376,"score :");
w->drawString(0,398,"level :");
w->drawString(0,420,"highscore :");
 w->drawString(100,376,"next :");
string result;
ostringstream convert;
convert<<score;
result=convert.str();
 string result2;
ostringstream convert2;
convert2<<level;
result2=convert2.str();
string result3;
ostringstream convert3;
convert3<<highscore;
result3=convert3.str();
w->drawString(50,376,result);
w->drawString(50,398,result2);
//w->drawString(70,410,result);*/
  }
}

void grid::turnon(int r,int c){
  thegrid[r][c].setliving();
  thegrid[r][c].setcelltype(b->gettype());
  //cout<<"blocklevel: "<<b->getlevel()<<endl;
  thegrid[r][c].setlevel(b->getlevel());
  //cout<<r<<c<<thegrid[r][c].getstatus()<<endl;
  if(w!=NULL){
    thegrid[r][c].draw();
  }
}
void grid::turnoff(int r,int c){
  thegrid[r][c].setdead();
  //cout<<1<<endl;
  thegrid[r][c].setcelltype(' ');
  //cout<<2<<endl;
  thegrid[r][c].setlevel(0);
  //cout<<3<<endl;
  if(w!=NULL){
  thegrid[r][c].undraw();
  }
}

void grid::initblock(char c){
  int x[4];
  int y[4];
  switch(c){
  case 'I':b=Block::geti();break;
  case 'J':b=Block::getj();break;
  case 'L':b=Block::getl();break;
  case 'O':b=Block::geto();break;
  case 'S':b=Block::gets();break;
  case 'Z':b=Block::getz();break;
  case 'T':b=Block::gett();break;
  }
  b->ChangeLevel(level);
  for (int i=0;i<4;i++){
    x[i]=b->getx(i);
    y[i]=b->gety(i);
  }
  for (int i=0;i<4;i++){
    //cout<<"turn initb"<<endl;
   turnon(y[i],x[i]);
   //w->Xwindow::fillRectangle(20*(x[i]+6),20*(y[i]+16),20,20);
   //cout<<"finished initb"<<endl;
   }
}
void grid::initnextblock(char c){
  int color;
  switch(c){
  case 'Z':nb=Block::getz();color=8;break;
  case 'I':nb=Block::geti();color=2;break;
  case 'J':nb=Block::getj();color=3;break;
  case 'S':nb=Block::gets();color=4;break;
  case 'L':nb=Block::getl();color=5;break;
  case 'O':nb=Block::geto();color=6;break;
    //case 'S':nb=Block::gets();color=4;break;
    //case 'Z':nb=Block::getz();color=1;break;
  case 'T':nb=Block::gett();color=7;break;
  }
//cout<<"initblock :"<<level<<endl;
  nb->ChangeLevel(level);
//cout<<"nextblock "<<level<<endl;
  for (int i=0;i<4;i++){
    int y=nb->gety(i);
    int x=nb->getx(i);
    //cout<<"nb "<<y<<x<<endl;
    if (w!=NULL){
      w->Xwindow::fillRectangle(20*(x+6),20*(y+16),20,20,color);
      w->Xwindow::fillRectangle(20*(x+6),20*(y+16),20,1,1);
      w->Xwindow::fillRectangle(20*(x+6),20*(y+16),1,20,1);
w->Xwindow::fillRectangle(20*(x+7),20*(y+16),1,20,1);
w->Xwindow::fillRectangle(20*(x+6),20*(y+17),20,1,1);
    }
  }
}

void grid::changeblock(){
  nb->reset();
  b=nb;
  for (int i=0;i<4;i++){
    int y=b->gety(i);
    int x=b->getx(i);
    if (thegrid[y][x].getstatus()){
      gg=true;
      break;
    }
    if (w!=NULL){
      w->Xwindow::fillRectangle(20*(x+6),20*(y+16),20,20,0);
w->Xwindow::fillRectangle(20*(x+7),20*(y+16),1,20,0);
w->Xwindow::fillRectangle(20*(x+6),20*(y+17),20,1,0);
    }
    turnon(y,x);
  }
}


void grid::cleargrid(){
  for(int i=0;i<csize;i++){
    delete [] thegrid[i];
  }
  delete [] thegrid;
  delete w;
}
void grid::clearline(int n){
  int nn=n;
  for (int j=0;j<csize;j++){
    if (thegrid[n][j].getalivenum()==0){
      //cout<<thegrid[n][j].getalivenum()<<endl;
      score=(thegrid[n][j].getlevel()+1)*(thegrid[n][j].getlevel()+1)+score;
      //cout<<score<<endl;
    }
    else{
      thegrid[n][j].notifyneighbour();
      //cout<<thegrid[n][1].getalivenum()<<endl;
    }
    turnoff(n,j);
  }
  //delete [] thegrid[n];
  for (;n>0;n--){
    for (int j=0;j<csize;j++){
      thegrid[n-1][j].setcoords(n,j,j*20,20*n,20,20,w);
      thegrid[n][j]=thegrid[n-1][j];
    }
  }
  for (int j=0;j<csize;j++){
    thegrid[0][j]=Cell();
    thegrid[0][j].setcoords(0,j,j*20,0*20,20,20,w);
    }
  for (;nn>0;nn--){
    for (int j=0;j<csize;j++){
      if (w!=NULL){
	if (thegrid[nn][j].getstatus()){
	  thegrid[nn][j].draw();
	}
	else{thegrid[nn][j].undraw();
	}
      }
    }
  }
}
void grid::clear(){
  //int r;
  int linesnum=0;
  for(int r=17;r>0;r--){
    int count=0;
    for(int j=0;j<csize;j++){
      if (thegrid[r][j].getstatus()){
	count++;
      }
      else{break;}
    }
    //cout<<r<<endl;
    if (count==10){
      //cout<<r<<endl;
      clearline(r);
      r++;
      linesnum++;
      }
  }
  if(linesnum!=0){
    cout<<"score after clearb: "<<score<<endl;
    cout<<"level: "<<level<<endl;
    score=(linesnum+level)*(linesnum+level)+score;
    cout<<"clear "<<linesnum<<" lines"<<endl;
    cout<<"score after clearline: "<<score<<endl;
    }
}



void grid::setlevel(int l){
  //level=l;
  cout<<"current level "<<level<<endl;
  cout<<"change to "<<l<<endl;
 if (w!=NULL){
   string result;
ostringstream convert;
convert<<level;
result=convert.str();
//cout<<"result "<<result<<endl;
 w->drawString(50,398,result,0);
  }
level=l;
 if (w!=NULL){
   string result2;
ostringstream convert2;
convert2<<level;
result2=convert2.str();
 cout<<"draw new level"<<endl;
w->drawString(50,398,result2);
 }
}

void grid::rotate(){
  //int x[4];
  //int y[4];
  for (int i=0;i<4;i++){
    turnoff(b->gety(i),b->getx(i));
    cout<<"coordinate "<<b->gety(i)<<" "<<b->getx(i)<<endl;
  }
  //cout<<"turnoff"<<endl;
  b->rotate();
  //cout<<b->gety(1)<<b->getx(1)<<endl;
  for (int j=0;j<4;j++){
    if (b->getx(j)>=csize){
      b->stepback();
      break;
    }
  }
  //cout<<"check rotate"<<endl;
  for(int i=0;i<4;i++){
    cout<<"coordinate after rotate"<<b->gety(i)<<" "<<b->getx(i)<<endl;
    turnon(b->gety(i),b->getx(i));
    //cout<<"turnon"<<endl;
    }
}


//int grid::rowdif(int r,int c){
//int baser=0;
//for (int baser;thegrid[i][c].isAlive;baser++){}
//r=r-baser;
//return r;
//}

//void grid::checkcoord(){
//int a[4];
//int b[4];
//for(int i=0;i<4;i++){
//  a[i]=b->y[i];
//  b[i]=b->x[i];
//}
//for (int i=0;i<4;i++){
//  if (thegrid[a[i]][[b[i]].isAlive){
//	return false;
//	break;
//    }
//    else{}
void grid::drop(){
string result;
ostringstream convert;
convert<<score;
result=convert.str();
  int r[4];
  int c[4];
  int d=0;
  for (int i=0;i<4;i++){
    r[i]=b->gety(i);
    c[i]=b->getx(i);
  }
  for (int i=0;i<4;i++){
    turnoff(r[i],c[i]);
    }
  //cout<<rsize<<endl;
  for (d=0;d<rsize-3;d++){
    if (thegrid[r[0]+d][c[0]].getstatus()||thegrid[r[1]+d][c[1]].getstatus()||thegrid[r[2]+d][c[2]].getstatus()||thegrid[r[3]+d][c[3]].getstatus()){
      d--;
      break;
    }
    if (r[0]+d>=17||r[1]+d>=17||r[2]+d>=17||r[3]+d>=17){
      break;
    }
  }
  for (int i=0;i<4;i++){
    turnon(r[i]+d,c[i]);
    for (int j=0;j<4;j++){
      if (i!=j){
	//cout<<"add"<<endl;
	thegrid[r[i]+d][c[i]].addneighbour(&(thegrid[r[j]+d][c[j]]));
      }
    }
    }
  //delete b;
  cout<<"drop get here"<<endl;
  clear();
  gameover();
  cout<<"drop then clear get here"<<endl;
  if (w!=NULL){
    cout<<"get l344"<<endl;
w->drawString(50,376,result,0);
 cout<<"getl l346"<<endl;
ostringstream convert2;
convert2<<score;
result=convert2.str();
w->drawString(50,376,result);
 cout<<"get l351"<<endl;  }
}

int grid::getlevel(){
  return level;
}

int grid::getscore(){
  return score;
}
int grid::gethighscore(){
  return highscore;
}

int grid::getrsize(){
  return rsize;
}
int grid::getcsize(){
  return csize;
}
void grid::printgrid(){
  for (int i=0;i<rsize;i++){
    for (int j=0;j<csize;j++){
      if (thegrid[i][j].getstatus()){
	cout<<thegrid[i][j].gettype();
      }
      else{
	cout<<' ';
      }
    }
    cout<<endl;
  }
}
void grid::shiftr(){
  //  int r[4];
  //int c[4];
  /*for (int i=0;i<4;i++){
    r[i]=b->gety(i);
    c[i]=b->getx(i);
    }*/
  for (int i=0;i<4;i++){
    turnoff(b->gety(i),b->getx(i));
  }
  b->shiftright();
  for (int i=0;i<4;i++){
    if (b->getx(i)>=csize){
      b->stepback();
      break;
    }
    else if (thegrid[b->gety(i)][b->getx(i)].getstatus()){
      b->stepback();
      break;
    }
  }
  for (int i=0;i<4;i++){
    turnon(b->gety(i),b->getx(i));
  }
}

void grid::shiftl(){
  for (int i=0;i<4;i++){
    turnoff(b->gety(i),b->getx(i));
  }
  b->shiftleft();
  for (int i=0;i<4;i++){
    if (b->getx(i)<0){
      b->stepback();
      break;
    }
    else if (thegrid[b->gety(i)][b->getx(i)].getstatus()){
      b->stepback();
      break;
    }
  }
  for (int i=0;i<4;i++){
    turnon(b->gety(i),b->getx(i));
  }
}

void grid::shiftd(){
  int d=true;
  for (int i=0;i<4;i++){
    if (b->gety(i)==17){
      d=false;
      break;
    }
  }
  if (d){
    for (int i=0;i<4;i++){
      turnoff(b->gety(i),b->getx(i));
      cout<<"in shiftdown turn off "<<b->gety(i)<<b->getx(i)<<endl;
    }
    b->shiftdown();
    for (int i=0;i<4;i++){
      if (thegrid[b->gety(i)][b->getx(i)].getstatus()){
	cout<<"in shiftdown need to back "<<b->gety(i)<<b->getx(i)<<endl;
	b->stepback();
	break;
      }
    /*cout<<b->gety(i)<<endl;
    if (b->gety(i)>=17){
      break;
      }*/
    }
    for (int i=0;i<4;i++){
      turnon(b->gety(i),b->getx(i));
      cout<<"after shiftdown: "<<b->gety(i)<<" "<<b->getx(i)<<endl;
    }
  }
}

void grid::gameover(){
  for (int j=0;j<csize;j++){
    if (thegrid[3][j].getstatus()){
      gg=true;
      break;
    }
  }
}

void grid::sethighscore(int h){
  string result;  
if (w!=NULL){
ostringstream convert;
convert<<highscore;
result=convert.str();
 w->drawString(70,420,result,0);
  }
 highscore=h;
 if (w!=NULL){
ostringstream convert2;
convert2<<highscore;
result=convert2.str();
 w->drawString(70,420,result);
 }
}

char grid::getnext(){
  return nb->gettype();
}

bool grid::getgg(){
  return gg;
}

void grid::setwindownull(){
  delete w;
  w=NULL;
}

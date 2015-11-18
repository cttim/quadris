#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "grid.h"
#include "scoreboard.h"

grid*g=new grid();
scoreboard *s=new scoreboard();


int getint(string a){
  int count=1;
  if (a[0]>'9'){
  }
  else{
    count=a[0]-'0';
    for(int i=1; a[i]<='9'; i++){
      count=count*10+a[i]-'0';
    }
  }
  return count;
}


bool search(string in,string out){
  unsigned int count=0;
  for (;in[count]<='9'; count++){}
  for (int i=0; i+count<in.length(); i++){
    if (in[i+count]!=out[i]){
      return false;
    }
  }
  return true;
}

string command[9]={"left","right","down","clockwise","counterclockwise","drop","levelup","leveldown","restart"};

char levelzero(int count,char* filename){
  char a;
  ifstream infile;
  infile.open(filename);
  if (infile.fail()){
    infile.clear();
    cerr<<"error 0:infile fail!!! Can u plz check if file readable?"<<endl;
    return '/';
  }
  for (int i=0;i<count;i++){
    if (infile>>a){}
    else {
      count=count-i;
      a=levelzero(count,filename);
      return a;
    }
  }
  return a;
}
char levelone(){
  int a=rand()%12+1;
    switch (a){
    case 1:
      return 'S';
      break;
    case 2:
      return 'Z';
      break;
    case 3:case 4:
      return 'I';
      break;
    case 5:case 6:
      return 'J';
      break;
    case 7:case 8:
      return 'L';
      break;
    case 9:case 10:
      return 'O';
      break;
    case 11:case 12:
      return 'T';
      break;
    }
    return '/';
}

char leveltwo(){
  int a=rand()%7+1;
    switch (a){
    case 1:
      return 'S';
      break;
    case 2:
      return 'Z';
      break;
    case 3:
      return 'I';
      break;
    case 4:
      return 'J';
      break;
    case 5:
      return 'L';
      break;
    case 6:
      return 'O';
      break;
    case 7:
      return 'T';
      break;
    }
    return '/';
}

char levelthree(){
  int a=rand()%9+1;
    switch (a){
    case 1:case 2:
      return 'S';
      break;
    case 3:case 4:
      return 'Z';
      break;
    case 5:
      return 'I';
      break;
    case 6:
      return 'J';
      break;
    case 7:
      return 'L';
      break;
    case 8:
      return 'O';
      break;
    case 9:
      return 'T';
      break;
    }
    return '/';
}
int count=0;
int main (int argc,char *argv[]){
  s->connectgrid(g);
  int comcount;
  char c;
  string com;
  char *filename=const_cast<char*>("sequence.txt");
  bool text_flag=false;
  for (int i=1;i<argc;i++){
    if (string(argv[i])=="-text"){text_flag=true;g->setwindownull();}
    if (string(argv[i])=="-seed"){srand(atoi(argv[i+1]));i++;}
    if (string(argv[i])=="-scriptfile"){filename=argv[i+1];i++;}
    if (string(argv[i])=="-startlevel"){g->setlevel(atoi(argv[i+1]));i++;}
  }
  g->init();
  int level=g->getlevel();
  int times;
  switch(level){
  case 0:
    c=levelzero(1, filename);
    if (c=='/'){
      cerr<<"open file failed"<<endl;
    }
    g->initblock(c);
    c=levelzero(2, filename);
    g->initnextblock(c);
    count=3;
    break;
  case 1:
    c=levelone();
    g->initblock(c);
    c=levelone();
    g->initnextblock(c);
    break;
  case 2:
    c=leveltwo();
    g->initblock(c);
    c=leveltwo();
    g->initnextblock(c);
    break;
  case 3:
    c=levelthree();
    g->initblock(c);
    c=levelthree();
    g->initnextblock(c);
    break;
  }
  s->printscore();
  while(cin>>com){
    //times=commandstart();
    for (comcount=0;comcount<9;comcount++){
      if(search(com,command[comcount])){
	break;
      }
    }
    if (comcount==9){
      cerr<<"error 2: command does not exist!!! check your command"<<endl;
    }
    else{
      times=getint(com);
      for (int i=0;i<times;i++){
	switch(comcount){
	case 0:
	  g->shiftl();
	  break;
	case 1:
	  g->shiftr();
	  break;
	case 2:
	  g->shiftd();
	  break;
	case 3:
	  g->rotate();
	  break;
	case 4:
	  g->rotate();
	  g->rotate();
	  g->rotate();
	  break;
	case 5:
	  g->drop();
	  if (g->getgg()){
	    cout<<"gameover"<<endl;
	    return 0;
	  }
	  g->changeblock();
	  if (g->getgg()){
	    cout<<"gameover"<<endl;
	    return 0;
	  }
	  if(g->getlevel()==0){
	    g->initnextblock(levelzero(count,filename));
	    count++;
	  }
	  else if(g->getlevel()==1){
	    g->initnextblock(levelone());
	  }
	  else if(g->getlevel()==2){
	    g->initnextblock(leveltwo());
	  }
	  else if(g->getlevel()==3){
	    g->initnextblock(levelthree());
	  }
	  break;
	case 6:
	  if(g->getlevel()==3){}
	  else{
	    g->setlevel(g->getlevel()+1);
	  }
	  break;
	case 7:
	  if(g->getlevel()==0){}
	  else{
	    g->setlevel(g->getlevel()-1);
	  }
	  break;
	case 8:
	  delete g;
	  g=new grid();
	  s->connectgrid(g);
	  g->init();
	  if (text_flag){
	    g->setwindownull();
	  }
	  count=0;
	  g->setlevel(level);
	  switch(level){
	  case 0:
	    c=levelzero(1, filename);
	    if (c=='/'){
	      cerr<<"open file failed"<<endl;
	    }
	    g->initblock(c);
	    c=levelzero(2, filename);
	    g->initnextblock(c);
	    count=3;
	    break;
	  case 1:
	    c=levelone();
	    g->initblock(c);
	    c=levelone();
	    g->initnextblock(c);
	    break;
	  case 2:
	    c=leveltwo();
	    g->initblock(c);
	    c=leveltwo();
	    g->initnextblock(c);
	    break;
	  case 3:
	    c=levelthree();
	    g->initblock(c);
	    c=levelthree();
	    g->initnextblock(c);
	    break;
	  }
	  s->printscore();
	  break;
	}
      }
    }
    s->printscore();
  }
  delete g;delete s;
}

#include "scoreboard.h"
#include <iostream>
#include <string>
#include "grid.h"
using namespace std;

scoreboard::scoreboard(){
  highscore=0;
  score=0;
  level=0;
}

scoreboard::~scoreboard(){}

void scoreboard::connectgrid(grid* a){
  g=a;
}

void scoreboard::setnext(char a){
  next=a;
}

void scoreboard::update(){
  score=g->getscore();
  level=g->getlevel();
  next=g->getnext();
  if (score>highscore){highscore=score;}
  g->sethighscore(highscore);
}

void scoreboard::printscore(){
  update();
  cout<<"Level:";
  cout<<"     ";
  cout<<level<<'\n';
  cout<<"Score:";
  cout<<"     ";
  cout<<score<<'\n';
  cout<<"Hi Score:";
  cout<<" ";
  cout<<highscore<<'\n';
  cout<<"____________"<<'\n';
  g->printgrid();
  cout<<"____________"<<'\n';
  cout<<"Next:"<<'\n';
  switch (next){
  case 'I':
    cout<<"IIII";
    break;
  case 'J':
    cout<<"J"<<'\n'<<"JJJ";
    break;
  case 'L':
    cout<<"  L"<<'\n'<<"LLL";
    break;
  case 'O':
    cout<<"OO"<<'\n'<<"OO";
    break;
  case 'S':
    cout<<" SS"<<'\n'<<"SS";
    break;
  case 'Z':
    cout<<"ZZ"<<'\n'<<" ZZ";
    break;
  case 'T':
    cout<<"TTT"<<'\n'<<" T";
    break;
  default:
    cout<<"not find....check driver";
    break;
  }
  cout<<'\n';
}

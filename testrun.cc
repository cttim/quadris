#include <iostream>
#include "grid.h"
#include "block.h"
using namespace std;
int main(){
  grid* d=new grid();
  d->init();
  string a;
  while(true){
    cin>>a;
    if (a=="bj"){
      d->initblock('J');
    }
    if (a=="bl"){
      d->initblock('L');
    }
    if (a=="bi"){
      d->initblock('I');
    }
    if (a=="r"){
      d->rotate();
    }
    if(a=="d"){
      d->drop();
    }
    if (a=="sr"){
      d->shiftr();
    }
    if (a=="sl"){
      d->shiftl();
    }
    if (a=="sd"){
      d->shiftd();
    }
    //d->printgrid();
  }
}

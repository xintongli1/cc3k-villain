#ifndef _DROW_
#define _DROW_
#include <iostream>
#include "player.h"

class Drow:public Player{


public:
  Drow(int row, int col,int chamber);
  void attackedBy(std::shared_ptr<Elf> c)override;
};

#endif

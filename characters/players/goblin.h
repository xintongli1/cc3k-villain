#ifndef _GOBLIN_
#define _GOBLIN_
#include <iostream>
#include "player.h"

class Goblin:public Player{


public:
  Goblin(int row, int col,int chamber);
  void attackedBy(std::shared_ptr<Orcs> c)override;
};

#endif

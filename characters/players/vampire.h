#ifndef _VAMPIRE_
#define _VAMPIRE_
#include <iostream>
#include "player.h"

class Vampire:public Player{


public:
  Vampire(int row, int col,int chamber);
  ~Vampire()=default;
  void attack(std::shared_ptr<Characters> c)override;
};

#endif

#ifndef _ORCS_
#define _ORCS_
#include <iostream>
#include "enemy.h"

class Orcs:public Enemy{


public:
  Orcs(int row, int col,int chamber);
  void attack(std::shared_ptr<Characters> c)override;
};

#endif

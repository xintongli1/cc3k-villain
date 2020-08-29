#ifndef _HALFLING_
#define _HALFLING_
#include <iostream>
#include "enemy.h"

class Halfling:public Enemy{

public:
  Halfling(int row, int col,int chamber);
  void attackedBy(std::shared_ptr<Characters>c) override;
  void attackedBy(std::shared_ptr<Vampire>c) override;
};

#endif

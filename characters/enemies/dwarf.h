#ifndef _DWARF_
#define _DWARF_
#include <iostream>
#include "enemy.h"

class Dwarf:public Enemy{


public:
  Dwarf(int row, int col,int chamber);
  void attackedBy(std::shared_ptr<Vampire> c)override;
};

#endif

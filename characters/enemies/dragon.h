#ifndef _DRAGON_
#define _DRAGON_
#include <iostream>
#include <memory>
#include "enemy.h"

class Treasure;

class Dragon:public Enemy{
  std::shared_ptr<Treasure> DragonHoard;
  bool treasureSafe;

public:
  Dragon(int row, int col,int chamber,std::shared_ptr<Treasure> DragonHoard );
  std::shared_ptr<Treasure> getDH();
};

#endif

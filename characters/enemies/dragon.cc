#include "dragon.h"

Dragon::Dragon(int r, int c,int ch,std::shared_ptr<Treasure> d):
  Enemy{r,c,"Dragon",ch,150,20,20,'D'}, DragonHoard{d}, treasureSafe{true}{
  }

std::shared_ptr<Treasure> Dragon::getDH(){
    return DragonHoard;
}

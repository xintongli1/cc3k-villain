#include "orcs.h"
Orcs::Orcs(int r, int c,int ch):
  Enemy{r,c,"Orcs",ch,180,30,25,'O'}{}

void Orcs::attack(std::shared_ptr<Characters> c){
    c->attackedBy(std::make_shared<Orcs>(*this));
}


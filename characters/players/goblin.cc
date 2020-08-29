#include "goblin.h"
#include "orcs.h"
#include <math.h>

Goblin::Goblin(int r, int c,int ch):
  Player{r,c,"Goblin",ch,110,15,20}{}

void Goblin::attackedBy(std::shared_ptr<Orcs>c){
    int damage = ceil((100.0 / (100 + this->getDef()))*(c->getAtk()));
    damage *= 1.5;
    this->setHP(-damage);
}



#include "halfling.h"
#include "vampire.h"
#include <math.h>

Halfling::Halfling(int r, int c,int ch):
  Enemy{r,c,"Halfling",ch,100,15,20,'L'}{}


void Halfling::attackedBy(std::shared_ptr<Characters>c){
    bool success = rand() % 2;
    if (success) {
      int damage = ceil((100.0 / (100 + this->getDef()))*(c->getAtk()));
      this->setHP(-damage);
    }
}
void Halfling::attackedBy(std::shared_ptr<Vampire>c) {
    bool success = rand() % 2;
    if (success) {
      int damage = ceil((100.0 / (100 + this->getDef()))*(c->getAtk()));
      this->setHP(-damage);
      c->setHP(5);
    }
}


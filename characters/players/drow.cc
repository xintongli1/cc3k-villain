#include "drow.h"
#include "elf.h"
#include <math.h>


Drow::Drow(int r, int c,int ch):
  Player{r,c,"Drow",ch,150,25,15}{}

  void Drow::attackedBy(std::shared_ptr<Elf>c) {
  bool success = rand() % 2;
  if (success) {
    int damage = ceil((100.0 / (100 + this->getDef()))*(c->getAtk()));
    this->setHP(-damage);
  } 
}


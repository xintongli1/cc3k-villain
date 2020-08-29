#include "dwarf.h"
#include "vampire.h"
#include <math.h>

Dwarf::Dwarf(int r, int c,int ch):
  Enemy{r,c,"Dwarf",ch,100,20,30,'W'}{}

/*char Dwarf::getChar() const{
  return c;
}*/

void Dwarf::attackedBy(std::shared_ptr<Vampire>c){
    int damage = ceil((100.0 / (100 + this->getDef()))*(c->getAtk()));
    this->setHP(-damage);
    c->setHP(-5);
}

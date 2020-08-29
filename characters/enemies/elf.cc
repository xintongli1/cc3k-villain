#include "elf.h"

Elf::Elf(int r, int c,int ch):
  Enemy{r,c,"Elf",ch,140,30,10,'E'}{}

/*char Elf::getChar() const{
  return c;
}*/

void Elf::attack(std::shared_ptr<Characters> c){
    c->attackedBy(std::make_shared<Elf>(*this));
}


#include "vampire.h"

Vampire::Vampire(int r, int c,int ch):
  Player{r,c,"Vampire",ch,50,25,25}{}

  void Vampire::attack(std::shared_ptr<Characters> c){
    c->attackedBy(std::make_shared<Vampire>(*this));
}

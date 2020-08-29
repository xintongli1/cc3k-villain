#include "characters.h"
#include "elf.h"
#include "vampire.h"
#include "orcs.h"
#include <math.h>
#include <iostream>

Characters::Characters(int r, int c, std::string t, int ch, int h, int a, int d):
  Object{r,c,t,ch},HP{h},atk{a},def{d}, dead{false}{
    MaxHP = h;
    initAtk = a;
    initDef = d;
    dead=false;
  }

Characters::~Characters(){
	observers.clear();
}

int Characters::getHP() const{
  return HP;
}

int Characters::getAtk() const{
  return atk;
}

int Characters::getDef() const{
  return def;
}

void Characters::resetStat(){
  atk = initAtk;
  def = initDef;
}

bool Characters::isDead() const{
  return dead;
}

void Characters::setHP(int n) {
  HP += n;
  HP = std::max(0, HP);
  HP = std::min(MaxHP, HP);
  if(HP==0){
    dead = true;
  }
}

void Characters::setAtk(int n) {
  atk = std::max(0, atk+n);
}

void Characters::setDef(int n) {
  def = std::max(0, def+n);
}

void Characters::setPos(int r, int c){
    row = r;
    col = c;
}

void Characters::setChamber(int ch){
	chamber = ch;
}

void Characters::setDead(bool t){
    dead = t;
}

void Characters::attach (std::shared_ptr<Object> o){
	observers.emplace_back(o);
}

void Characters::attackedBy(std::shared_ptr<Characters> c) {
  int damage = ceil((100.0 / (100 + def))*(c->getAtk()));
  this->setHP(-damage);
  if (HP <= 0) dead = true;
}

void Characters::attackedBy(std::shared_ptr<Elf> c) {
    //std::cout<<"elf special"<<std::endl;
  for (int i = 0; i < 2; i++) {
    bool success = rand() % 2;
    if (success) {
      int damage = ceil((100.0 / (100 + def))*(c->getAtk()));
      this->setHP(-damage);
      if (HP <= 0) dead = true;
    }
  }
}

void Characters::attackedBy(std::shared_ptr<Vampire> c) {
    //std::cout<<"vamp special"<<std::endl;
  int damage = ceil((100.0 / (100 + def))*(c->getAtk()));
  this->setHP(-damage);
  c->setHP(5);
  if (HP <= 0) dead = true;
}

void Characters::attackedBy(std::shared_ptr<Orcs> c) {
    //std::cout<<"orcs special"<<std::endl;
  int damage = ceil((100.0 / (100 + def))*(c->getAtk()));
  this->setHP(-damage);
  if (HP <= 0) dead = true;
}





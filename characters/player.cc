#include "characters.h"
#include "player.h"
#include <algorithm>
#include <math.h>
#include "enemy.h"
using namespace std;

Player::Player(int r, int c, std::string t, int ch, int h, int a, int d):
  Characters{r,c,t,ch,h,a,d}, gold{0}, cellOccupied{'.'} {
    /*MaxHP = h;
    initAtk = a;
    initDef = d;*/
    //dead=false;
}

int Player::getGold() const{
  return gold;
}

/*bool Player::isDead() const{
  return dead;
}*/

char Player::getChar() const{
  return c;
}

void Player::attack(std::shared_ptr<Characters> c){
    c->Characters::attackedBy(std::make_shared<Player>(*this));
    //this->attackedBy(c);
    //std::cout<<this->getType()<<" attacked "<<c->getType()<<std::endl;
    //std::cout<<"player"<<std::endl;
}

/*void Player::resetStat(){
  atk = initAtk;
  def = initDef;
}

void Player::setHP(int n) {
  HP += n;
  HP = max(0, HP);
  HP = min(MaxHP, HP);
  if(HP==0){
    dead = true;
  }
}

void Player::setAtk(int n) {
  atk = max(0, atk+n);
}

void Player::setDef(int n) {
  def = max(0, def+n);
}*/

void Player::addGold(int n) {
  gold += n;
}


std::string Player::info(){
    std::string a;
    a=this->getChar();
    std::string b;
    b = to_string(this->getGold());
    std::string c;
    c=to_string(this->getHP());
    std::string d;
    d=to_string(this->getAtk());
    std::string e;
    e=to_string(this->getDef());
    std::string s=" char is: "+a+" gold is: "+b+" HP is: "+c+" Atk is: "+d+" Def is: "+e;
    std::cout<<s;
    return s;
}


/*void setChamber(int ch){
	chamber = ch;
}*/

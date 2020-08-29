#ifndef _PLAYER_
#define _PLAYER_
#include <iostream>
#include "characters.h"

class Player:public Characters{
  static const char c = '@';
  char cellOccupied;
  /*int MaxHP;
  int initAtk;
  int initDef;*/
  int gold;
  //bool dead;
public:
  Player(int row, int col, std::string type, int chamber, int HP, int atk, int def);

  //void setChamber(int ch);
  //void resetStat();

  int getGold() const;
  //bool isDead() const;
  char getChar() const;
  /*virtual void setHP(int n) override;
  void setAtk(int n);
  void setDef(int n);*/
  void addGold(int n);
  //a helper to see current info
  std::string info();
  void attack(std::shared_ptr<Characters> c) override;

  //virtual void usePotion(std::shared_ptr<Potion> p);

};

#endif

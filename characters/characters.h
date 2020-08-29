#ifndef _CHARACTER_
#define _CHARACTER_
#include <iostream>
#include <vector>
#include <memory>
#include "object.h"

class Elf;
class Vampire;
class Orcs;

class Characters:public Object{
  int HP;
  int atk;
  int def;
  int MaxHP;
  int initAtk;
  int initDef;
  bool dead;

protected:

  std::vector<std::shared_ptr<Object>> observers;

public:
  Characters(int row, int col, std::string type, int chamber, int HP, int atk, int def);
  ~Characters();
  int getHP() const;
  int getAtk() const;
  int getDef() const;
  bool isDead() const;
  void setAtk(int n);
  void setDef(int n);
  void setHP(int n);
  void setDead(bool t = true);
  void setChamber(int ch);
  void resetStat();

  void setPos(int r, int c);
  void attach (std::shared_ptr<Object> );

  virtual void attack(std::shared_ptr<Characters> c) = 0;
    virtual void attackedBy(std::shared_ptr<Characters> c);
    virtual void attackedBy(std::shared_ptr<Elf> c);
    virtual void attackedBy(std::shared_ptr<Vampire> c);
    virtual void attackedBy(std::shared_ptr<Orcs> c);

  //for later use...
  /*
  virtual void attack(std::shared_ptr<Characters> c) = 0;

  virtual void attackedBy(std::shared_ptr<Charactesr> c);
  virtual void attackedBy(std::shared_ptr<Human> c);
  virtual void attackedBy(std::shared_ptr<Dwarf> c);
  virtual void attackedBy(std::shared_ptr<Elf> c);
  virtual void attackedBy(std::shared_ptr<Orcs> c);
  virtual void attackedBy(std::shared_ptr<Merchant> c);
  virtual void attackedBy(std::shared_ptr<Dragon> c);
  virtual void attackedBy(std::shared_ptr<Halfling> c);

  virtual void attackedBy(std::shared_ptr<Shade> c);
  virtual void attackedBy(std::shared_ptr<Drow> c);
  virtual void attackedBy(std::shared_ptr<Vampire> c);
  virtual void attackedBy(std::shared_ptr<Troll> c);
  virtual void attackedBy(std::shared_ptr<Goblin> c);

  */

};

#endif

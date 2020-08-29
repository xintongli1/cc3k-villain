#ifndef _ENEMY_
#define _ENEMY_
#include <iostream>
#include "characters.h"

class Enemy:public Characters{
	 // helper function
	bool condition (bool rowGreater, bool colGreater, std::shared_ptr<Object> & o); // helper function

protected:
	//static 
  const char c;

public:
  Enemy(int row, int col, std::string type, int chamber, int HP, int atk, int def, char cha);
  void makeAction();
  std::string info();
  char getChar() const;
  void attack(std::shared_ptr<Characters> c) override;
  void attackedBy(std::shared_ptr<Characters> c) override;
    //void randomMove();
    //friend class Floor;
  //virtual void setHP(int n) override;
};

#endif

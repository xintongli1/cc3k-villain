#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include <map>
#include <memory>
#include "stairs.h"
#include "item.h"
#include "dragon.h"
#include "human.h"
#include "merchant.h"
#include "elf.h"
#include "halfling.h"
#include "orcs.h"
#include "dwarf.h"

class DragonHoard;

class Chamber{
    int id;
	std::map<int, std::map<int, std::shared_ptr<Cell>>> cells;
	std::vector<std::shared_ptr<Enemy>> enemies;
  	std::map<int, std::map<int, std::shared_ptr<Item>>> items;
	std::shared_ptr<Stairs> stairs;

	public:
	Chamber(int i);
	~Chamber();
    //void generateGold(int g);
    //void generatePotion(int p);
    //void generateStair();
    //void generateEnemy(int e);
    //void generateDragon(int i, int j, std::shared_ptr<DragonHoard> dh);
	friend class Floor;
	friend class FloorDisplay;

};


#endif

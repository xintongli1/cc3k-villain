#include "chamber.h"
using namespace std;

Chamber::Chamber(int i): id{i}{

}

Chamber::~Chamber(){
	for (auto & r: cells){
		r.second.clear();
	}
	cells.clear();

	for (auto & r: items){
		r.second.clear();
	}
	items.clear();

	/*
  for (auto & r: enemies){
		r.clear();
	}
*/
	enemies.clear();
}


//void generateGold(int g);
//void generatePotion(int p);
//void generateStair();
//void generateEnemy(int e);
//void generateDragon(int i, int j, std::shared_ptr<DragonHoard> dh);



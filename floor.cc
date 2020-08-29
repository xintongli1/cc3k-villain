#include "floor.h"
#include "wall.h"
#include "passage.h"
#include "door.h"
#include "tile.h"
#include "shade.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"
#include "small.h"
#include "normal.h"
#include "dragonHoard.h"
#include "merchantHoard.h"
#include "potion.h"
#include "ba.h"
#include "wa.h"
#include "bd.h"
#include "wd.h"
#include "ph.h"
#include "rh.h"
#include "floorDisplay.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
    
Floor::Floor(): level{1}, enemyStop{false}, generateItem{true}, end{false} {
    for (int i = 0; i < 25; ++i){
        vector<int> haha;
        vector<char> aha;
        for (int j = 0; j < 79; ++j){
            int t = -1;
            haha.emplace_back(t);
            char tt = '*';
            aha.emplace_back(tt);
        }
        status.emplace_back(haha);
        charStatus.emplace_back(aha);
    }
}

void Floor::init(std::unique_ptr<std::ifstream> infile){
    string ss;	
    getline(*infile, ss);
    int chamberNumber = -1;
    for (int i = 1; i < 24; ++i){
        getline(*infile, ss);
        //cout << "getline " << i << endl;
        for (int j = 1; j < 78; ++j){
            int up = status[i-1][j];
            int left = status[i][j-1]; 

            switch(ss[j]){
                case '|':
                    charStatus[i][j] = '|';
                    if ((up == -1 || up == 9) && (charStatus[i][j-1] != '-')){
                        ++chamberNumber;
                        status[i][j] = chamberNumber;
                        Chamber c{chamberNumber};
                        chambers.emplace_back(c);
                        map<int, shared_ptr<Cell>> t;
                        t.emplace(j, make_shared<Wall>(Wall{i, j, chamberNumber, '|'}));
                        chambers[chamberNumber].cells.emplace(i,t);
                        //cout << endl << "successful initializing a chamber" << endl;
                    }
                    else{
                        if (up != -1 && up != 9){
                            status[i][j] = up;
                            if (chambers[up].cells.count(i) == 0){
                                map<int, shared_ptr<Cell>> t;
                                t.emplace(j, make_shared<Wall>(Wall{i, j, up, '|'}));
                                chambers[up].cells.emplace(i,t);
                            }
                            else chambers[up].cells[i].emplace(j, make_shared<Wall>(Wall{i, j, up, '|'}));

                            if (left != -1 && left != 9 && up != left){
                                if (left < up){
                                    adjust(up, left);
                                }
                                else adjust(left,up); 
                                --chamberNumber; // only works for common cases
                            }
                        }
                        else{
                            status[i][j] = left;
                            chambers[left].cells[i].emplace(j, make_shared<Wall>(Wall{i, j, left, '|'}));
                        }
                    }

                    break;

                case '-':
                    charStatus[i][j] = '-';
                    status[i][j] = left;
                    chambers[left].cells[i].emplace(j, make_shared<Wall>(Wall{i, j, left, '-'}));
                    break;

                case ' ':
					charStatus[i][j] = ' ';
                    break;

                case '+':
                    charStatus[i][j] = '+';
                    if(left == -1 || left == 9){
                        status[i][j] = up;
                        if (chambers[up].cells.count(i) == 0){
                            map<int, shared_ptr<Cell>> t;
                            t.emplace(j, make_shared<Door>(Door{i, j, up}));
                            chambers[up].cells.emplace(i,t);
                        }
                        else chambers[up].cells[i].emplace(j, make_shared<Door>(Door{i, j, up}));
                    }
                    else{
                        status[i][j] = left;
                        chambers[left].cells[i].emplace(j, make_shared<Door>(Door{i, j, left}));
                    } 
                    break;

                case '#':
                    charStatus[i][j] = '#';
                    status[i][j] = 9; 
					if (passages.count(i) == 0){
						map<int, shared_ptr<Passage>> tt;
						tt.emplace(j, make_shared<Passage>(Passage{i, j}));
						passages.emplace(i, tt);
					}
					else{
						passages[i].emplace(j, make_shared<Passage>(Passage{i, j}));
					}
                    break;

                case '.':
                    charStatus[i][j] = '.';
                    status[i][j] = left;
                    chambers[left].cells[i].emplace(j, make_shared<Tile>(Tile{i, j, left}));
                    break;

                default: // treat as tile
					generateItem = false;
                    charStatus[i][j] = '.';
                    status[i][j] = left;
					shared_ptr<Tile> tl = make_shared<Tile>(Tile{i, j, left});
					tl->setOccupied(true);
					switch(ss[j]){
						case '0':
							tl->setObject(make_shared<RH>(RH{i, j, left}));
							break;
						case '1':
							tl->setObject(make_shared<BA>(BA{i, j, left}));
							break;
						case '2':
							tl->setObject(make_shared<BD>(BD{i, j, left}));
							break;
						case '3':
							tl->setObject(make_shared<PH>(PH{i, j, left}));
							break;
						case '4':
							tl->setObject(make_shared<WA>(WA{i, j, left}));
							break;
						case '5':
							tl->setObject(make_shared<WD>(WD{i, j, left}));
							break;
						case '6':
							tl->setObject(make_shared<Normal>(Normal{i, j, left}));
							break;
						case '7': 
							tl->setObject(make_shared<Small>(Small{i, j, left}));
							break;
						case '8':
							tl->setObject(make_shared<MerchantHoard>(MerchantHoard{i, j, left}));
							break;
						case '9':
							tl->setObject(make_shared<DragonHoard>(DragonHoard{i, j, left}));
							spawnDragon(i, j, left, dynamic_pointer_cast<DragonHoard>(tl->getObject()));
							break;
					}
                    chambers[left].cells[i].emplace(j, tl);
                    break;
            }
                //cout << charStatus[i][j] << " ";
        }
            //cout << endl;
    }

    /*
    for (int i = 1; i < 24; ++i){
        for (int j = 1; j < 78; ++j){
            cout << status[i][j] << ' ';
        }
        cout << endl;
    }
    */

}

Floor::~Floor(){
    chambers.clear();
    for (auto & r: status){
        r.clear();
    }
    status.clear();
    for (auto & r: charStatus){
        r.clear();
    }
    charStatus.clear();

	for (auto & r : passages){
		r.second.clear();
	}
	passages.clear();
}

void Floor::adjust(int chamberAdjusted, int indicator){
    int ch = indicator;
    for (auto & r : chambers[chamberAdjusted].cells){
        for (auto & c : r.second){
            shared_ptr<Cell>cel = c.second;
            if (chambers[ch].cells.count(cel->getRow()) == 0){
                map<int, shared_ptr<Cell>> tmp;
                tmp.emplace(cel->getCol(), cel);
                chambers[ch].cells.emplace(cel->getRow(), tmp);
            }
            else{
                chambers[ch].cells[cel->getRow()].emplace(cel->getCol(), cel);
            }
            status[cel->getRow()][cel->getCol()] = ch;
        }
    } 

    for (auto & r: chambers[chamberAdjusted].cells){
        r.second.clear();
    }
    chambers[chamberAdjusted].cells.clear();
}



bool Floor::checkForDragon(int x, int y) {
  int cn = status[x][y];
  if (charStatus[x-1][y] == '.') {
    shared_ptr<Tile> t1 = dynamic_pointer_cast<Tile>(chambers[cn].cells[x][y]);
    if ((t1->getOccupied()) && (t1->getObject()->getType() == "Dragon")) {
        shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(t1->getObject());
       if (!dr->isDead()) return true;
    }
  } else if (charStatus[x+1][y] == '.') {
    shared_ptr<Tile> t2 = dynamic_pointer_cast<Tile>(chambers[cn].cells[x][y]);
    if ((t2->getOccupied()) && (t2->getObject()->getType() == "Dragon")) {
        shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(t2->getObject());
       if (!dr->isDead()) return true;
      return true;
    }
  } else if (charStatus[x][y+1] == '.') {
    shared_ptr<Tile> t3 = dynamic_pointer_cast<Tile>(chambers[cn].cells[x][y]);
    if ((t3->getOccupied()) && (t3->getObject()->getType() == "Dragon")) {
        shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(t3->getObject());
       if (!dr->isDead()) return true;
      return true;
    }
  } else if (charStatus[x][y-1] == '.') {
    shared_ptr<Tile> t4 = dynamic_pointer_cast<Tile>(chambers[cn].cells[x][y]);
    if ((t4->getOccupied()) && (t4->getObject()->getType() == "Dragon")) {
        shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(t4->getObject());
       if (!dr->isDead()) return true;
      return true;
    }
  } else if (charStatus[x-1][y+1] == '.') {
    shared_ptr<Tile> t5 = dynamic_pointer_cast<Tile>(chambers[cn].cells[x][y]);
    if ((t5->getOccupied()) && (t5->getObject()->getType() == "Dragon")) {
        shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(t5->getObject());
       if (!dr->isDead()) return true;
      return true;
    }
  } else if (charStatus[x-1][y-1] == '.') {
    shared_ptr<Tile> t6 = dynamic_pointer_cast<Tile>(chambers[cn].cells[x][y]);
    if ((t6->getOccupied()) && (t6->getObject()->getType() == "Dragon")) {
        shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(t6->getObject());
       if (!dr->isDead()) return true;
      return true;
    }
  } else if (charStatus[x+1][y+1] == '.') {
    shared_ptr<Tile> t7 = dynamic_pointer_cast<Tile>(chambers[cn].cells[x][y]);
    if ((t7->getOccupied()) && (t7->getObject()->getType() == "Dragon")) {
        shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(t7->getObject());
       if (!dr->isDead()) return true;
      return true;
    }
  } else if (charStatus[x+1][y-1] == '.') {
    shared_ptr<Tile> t8 = dynamic_pointer_cast<Tile>(chambers[cn].cells[x][y]);
    if ((t8->getOccupied()) && (t8->getObject()->getType() == "Dragon")) {
        shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(t8->getObject());
       if (!dr->isDead()) return true;
      return true;
    }
  }
    return false;
}

bool Floor::getEnd() {
  return end;
}

void Floor::randomMove(std::shared_ptr<Enemy> e){
    std::vector<std::shared_ptr<Tile>> pos;
    int x = e->getRow(), y = e->getCol();
    for (int i = x - 1; i < x + 2; ++i){
        for (int j = y - 1; j < y + 2; ++j){
            if (! (i == x && j == y)){
                if(charStatus[i][j] == '.'){
                    std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (chambers[e->getChamberNumber()].cells[i][j]);
                    if(!oo->getOccupied()) {
                        pos.emplace_back(oo);
                    }

                }
            }
        }
    }

    if (pos.size() > 0){
        srand(time(NULL));
        int t = rand() % pos.size();
        e->setPos(pos[t]->getRow(), pos[t]->getCol());
        pos[t]->setOccupied(true);
        pos[t]->setObject(e);
        std::shared_ptr<Tile> ot = std::dynamic_pointer_cast<Tile> (chambers[e->getChamberNumber()].cells[x][y]);
        ot->setOccupied(false);
        ot->setObject(nullptr);
    }
}

void Floor::generatePC(char race) {
    srand(time(NULL));
    //player location
    std::vector<std::shared_ptr<Tile>> pos;
    int cn = rand() % 5;
    for (auto & it : chambers[cn].cells){
        for (auto & t : it.second){
            if (t.second->getType() == "tile"){
                std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (t.second);
                if (!oo->getOccupied()) pos.emplace_back(oo);
            }
        }
    }
    int sn = rand() % pos.size();
    int x = pos[sn]->getRow();
    int y = pos[sn]->getCol();


     switch (race) {
        case 's':
            pc = std::make_shared<Shade>(Shade{x, y, cn});
            break;
        case 'd':
            pc = std::make_shared<Drow>(Drow{x, y, cn});
            break;
        case 'v':
            pc = std::make_shared<Vampire>(Vampire{x, y, cn});
            break;
        case 'g':
            pc = std::make_shared<Goblin>(Goblin{x, y, cn});
            break;
        case 't':
            pc = std::make_shared<Troll>(Troll{x, y, cn});
            break;
        default:
            pc = std::make_shared<Shade>(Shade{x, y, cn});
            break;
    }
    pos[sn]->setOccupied(true);
	pos[sn]->setObject(pc);
}

void Floor::generate() {
    //srand(time(0));
  //make sure all cells are not Occupied
  for (int i = 0; i < 25; ++i) {
    for (int j = 0; j < 79; ++j) {
        if (charStatus[i][j] == '.') {
          shared_ptr<Tile> t = dynamic_pointer_cast<Tile>(chambers[status[i][j]].cells[i][j]);
          t->setOccupied(false);
        }
    }
  }
  if (pc != nullptr) {
    //initial atk and def
      pc->resetStat();
    //player location
      std::vector<std::shared_ptr<Tile>> pos;
      int cn = rand() % 5;
      for (auto & it : chambers[cn].cells){
          for (auto & t : it.second){
              if (t.second->getType() == "tile"){
                  std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (t.second);
                  if (!oo->getOccupied()) pos.emplace_back(oo);
              }
          }
      }
      int sn = rand() % pos.size();
      int x = pos[sn]->getRow();
      int y = pos[sn]->getCol();
      pos[sn]->setOccupied(true);
      pos[sn]->setObject(pc);
      pc->setPos(x, y);
  }
   else {
    //default
    generatePC('s');
  }
  message += "Player character has spawned.";

  //generate stair
    std::vector<std::shared_ptr<Tile>> ppos;
    int cnn = rand() % 5;
    for (auto & it : chambers[cnn].cells){
        for (auto & t : it.second){
            if (t.second->getType() == "tile"){
                std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (t.second);
                if (!oo->getOccupied()) ppos.emplace_back(oo);
            }
        }
    }
    //srand(time(NULL));
    int x1 = rand() % ppos.size();
    shared_ptr<Stairs> s = make_shared<Stairs>(ppos[x1]->getRow(),ppos[x1]->getCol(),cnn); 
    ppos[x1]->setOccupied(true);
    ppos[x1]->setObject(s);
    chambers[cnn].stairs = s;
  
  if(!generateItem){
	  
//generate potion
for(int i = 0; i < 10; i++) {
  // 0-BA,1-WA,2-BD,3-WD,4-PH,5-RH 
  int p = rand() % 6;
    std::vector<std::shared_ptr<Tile>> pos;
    int cn = rand() % 5;
    for (auto & it : chambers[cn].cells){
        for (auto & t : it.second){
            if (t.second->getType() == "tile"){
                std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (t.second);
                if (!oo->getOccupied()) pos.emplace_back(oo);
            }
        }
    }
    int sn = rand() % pos.size();
    int x = pos[sn]->getRow();
    int y = pos[sn]->getCol();


    switch (p) {
        case 0:{
        shared_ptr<BA> ba = make_shared<BA>(x,y,cn);
          if (chambers[cn].items.count(x) == 0) {
            map<int, shared_ptr<BA>> t;
            t.emplace(y, ba);
            //chambers[cn].items.emplace(x,t);
            shared_ptr<Item> bb = dynamic_pointer_cast<Item>(ba);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,bb));
          } else {
            chambers[cn].items[x].emplace(y, ba);
          }
          pos[sn]->setObject(ba);
          break;}
      case 1:{
        shared_ptr<WA> wa = make_shared<WA>(x,y,cn);
        if (chambers[cn].items.count(x) == 0) {
          map<int, shared_ptr<WA>> t;
          t.emplace(y, wa);
          //chambers[cn].items.emplace(x,t);
          shared_ptr<Item> tt = dynamic_pointer_cast<Item>(wa);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,tt));
        } else {
          chambers[cn].items[x].emplace(y, wa);
        }
        pos[sn]->setObject(wa);
          break;}
      case 2:{
        shared_ptr<BD> bd = make_shared<BD>(x,y,cn);
        if (chambers[cn].items.count(x) == 0) {
          map<int, shared_ptr<BD>> t;
          t.emplace(y, bd);
          shared_ptr<Item> tt = dynamic_pointer_cast<Item>(bd);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,tt));
          //chambers[cn].items.emplace(x,t);
        } else {
          chambers[cn].items[x].emplace(y, bd);
        }
        pos[sn]->setObject(bd);
          break;}
      case 3:{
        shared_ptr<WD> wd = make_shared<WD>(x,y,cn);
        if (chambers[cn].items.count(x) == 0) {
          map<int, shared_ptr<WD>> t;
          t.emplace(y, wd);
          //chambers[cn].items.emplace(x,t);
          shared_ptr<Item> tt = dynamic_pointer_cast<Item>(wd);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,tt));
        } else {
          chambers[cn].items[x].emplace(y, wd);
        }
        pos[sn]->setObject(wd);
          break;}
      case 4:{
        shared_ptr<PH> ph = make_shared<PH>(x,y,cn);
        if (chambers[cn].items.count(x) == 0) {
          map<int, shared_ptr<PH>> t;
          t.emplace(y, ph);
          //chambers[cn].items.emplace(x,t);
          shared_ptr<Item> tt = dynamic_pointer_cast<Item>(ph);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,tt));
        } else {
          chambers[cn].items[x].emplace(y, ph);
        }
        pos[sn]->setObject(ph);
          break;}
      case 5:{
        shared_ptr<RH> rh = make_shared<RH>(x,y,cn);
        if (chambers[cn].items.count(x) == 0) {
          map<int, shared_ptr<RH>> t;
          t.emplace(y, rh);
          shared_ptr<Item> tt = dynamic_pointer_cast<Item>(rh);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,tt));
          //chambers[cn].items.emplace(x,t);
        } else {
          chambers[cn].items[x].emplace(y, rh);
        }
        pos[sn]->setObject(rh);
          break;}
    }
    pos[sn]->setOccupied(true);
  }
}
 
//generate gold
for(int i = 0; i < 10; i++) {
  // 0,1,2,3,4-normal,5,6-small,7-dragonhoard      
    std::vector<std::shared_ptr<Tile>> pos;
    int cn = rand() % 5;
    for (auto & it : chambers[cn].cells){
        for (auto & t : it.second){
            if (t.second->getType() == "tile"){
                std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (t.second);
                if (!oo->getOccupied()) pos.emplace_back(oo);
            }
        }
    }
    int sn = rand() % pos.size();
    int x = pos[sn]->getRow();
    int y = pos[sn]->getCol();
    int g = rand() % 8;
    if (g < 5) {
        shared_ptr<Normal> n = make_shared<Normal>(x,y,cn);
        if (chambers[cn].items.count(x) == 0) {
          map<int, shared_ptr<Normal>> t;
          t.emplace(y, n);
          shared_ptr<Item> ss = dynamic_pointer_cast<Item>(n);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,ss));
        } else {
          chambers[cn].items[x].emplace(y, n);
        }
        pos[sn]->setObject(n);
    } else if (g < 7) {
        shared_ptr<Small> s = make_shared<Small>(x,y,cn);
        if (chambers[cn].items.count(x) == 0) {
          map<int, shared_ptr<Small>> t1;
          t1.emplace(y, s);
          shared_ptr<Item> ss = dynamic_pointer_cast<Item>(s);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,ss));
        } else {
          chambers[cn].items[x].emplace(y, s);
        }
        pos[sn]->setObject(s);
    } else {
        shared_ptr<DragonHoard> dh = make_shared<DragonHoard>(x,y,cn);
        if (chambers[cn].items.count(x) == 0) {
          map<int, shared_ptr<DragonHoard>> t2;
          t2.emplace(y, dh);
          shared_ptr<Item> dd = dynamic_pointer_cast<Item>(dh);
            chambers[cn].items[x].insert(pair<int,std::shared_ptr<Item>>(y,dd));
          //chambers[cn].items.emplace(x,t2);
          } else {
          chambers[cn].items[x].emplace(y, dh);
        }
        //spawn a Dragon
         // 0-no,1-so,2-ea,3-we,4-ne,5-nw,6-se,7-sw
		 spawnDragon(x, y, cn, dh);
         pos[sn]->setObject(dh);
    }
    pos[sn]->setOccupied(true);
  }


//generate enemies
// 0-3 = human,4-6 = dwarf, 7-11 = halfling, 12-13 = elf
//14-15 = orc, 16-17 = merchant
for(int i = 0; i < 20; i++) {
    std::vector<std::shared_ptr<Tile>> pos;
    int cn = rand() % 5;
    for (auto & it : chambers[cn].cells){
        for (auto & t : it.second){
            if (t.second->getType() == "tile"){
                std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (t.second);
                if (!oo->getOccupied()) pos.emplace_back(oo);
            }
        }
    }
    int sn = rand() % pos.size();
    int x = pos[sn]->getRow();
    int y = pos[sn]->getCol();

    int e = rand() % 18;
    if (e < 4) {
        shared_ptr<Human> h = make_shared<Human>(x,y,cn);
        chambers[cn].enemies.push_back(h);
        pos[sn]->setObject(h);
   } else if (e < 7) {
     shared_ptr<Dwarf> f = make_shared<Dwarf>(x,y,cn);
     chambers[cn].enemies.push_back(f);
     pos[sn]->setObject(f);
   } else if (e < 12) {
       shared_ptr<Halfling> l = make_shared<Halfling>(x,y,cn);
       chambers[cn].enemies.push_back(l);
       pos[sn]->setObject(l);
   } else if (e < 14) {
       shared_ptr<Elf> el = make_shared<Elf>(x,y,cn);
       chambers[cn].enemies.push_back(el);
       pos[sn]->setObject(el);
   } else if (e < 16) {
       shared_ptr<Orcs> o = make_shared<Orcs>(x,y,cn);
       chambers[cn].enemies.push_back(o);
       pos[sn]->setObject(o);
   } else {
       shared_ptr<Merchant> m = make_shared<Merchant>(x,y,cn);
       chambers[cn].enemies.push_back(m);
       pos[sn]->setObject(m);
   }
    pos[sn]->setOccupied(true);
    }
}

void Floor::setObservers(shared_ptr<Characters> chrct){
    int r = chrct->getRow();
    int c = chrct->getCol();
    int ch = chrct->getChamberNumber();

    auto enemies = chambers[ch].enemies;
    auto cells = chambers[ch].cells;
    auto items = chambers[ch].items;
    auto stairs = chambers[ch].stairs;

    for (int i = r - 1; i < r + 2; ++i){
        for (int j = c - 1; j < c + 2; ++j){
            if (! (i == r && j == c) ){
                if (enemies.size () > 0){
                    auto enemy = find_if(enemies.begin(), enemies.end(), [i, j](shared_ptr<Enemy> e){
                            return e->getRow() == i && e->getCol() == j;
                            });
                    if (*enemy != enemies.back()){
                        if ((*enemy)->isDead()){
                            chambers[ch].enemies.erase(enemy);
                        }
                        else chrct->attach(*enemy);
                    }
                    else{
                        if ((*enemy)->getRow() == i && (*enemy)->getCol() == j){
                            if ((*enemy)->isDead()){
                                chambers[ch].enemies.erase(enemy);
                            }
                            else chrct->attach(*enemy);
                        }
                    }
                }
                
                if (cells.count(i) && cells[i].count(j)){
                    chrct->attach(cells[i][j]);
                }

                if (items.size() > 0 && items.count(i) && items[i].count(j)){
                    chrct->attach(items[i][j]);
                }

                if (stairs && stairs->getRow() == i && stairs->getCol() == j){
                    chrct->attach(stairs);
                }
            }

        }
    }
}

void Floor::PCAction(char mode, const std::string & direction){
	// ----sort enemies----
	for(auto & chmbr : chambers){
		sort(chmbr.enemies.begin(), chmbr.enemies.end(), [](shared_ptr<Enemy> & l, shared_ptr<Enemy> & r){
			if (l->getRow() != r->getRow()){
				return l->getRow() < r->getRow();
			}
			else{
				return l->getCol() < r->getCol();
			}
		});
	}
	//---------------------

	message.clear();
	message = "PC";
    int r = pc->getRow();
    int c = pc->getCol();
    int nr, nc;
    string d;
    if (direction == "no"){
        nr = r - 1;
        nc = c;
        d = "North";
    } 
    else if (direction == "so"){
        nr = r + 1;
        nc = c;
        d = "South";
    }
    else if (direction == "ea"){
        nr = r;
        nc = c + 1;
        d = "East";
    }
    else if(direction == "we"){
        nr = r;
        nc = c - 1;
        d = "West";
    }
    else if (direction == "ne"){
        nr = r - 1;
        nc = c + 1;
        d = "North East";
    }
    else if(direction == "nw"){
        nr = r - 1;
        nc = c - 1;
        d = "North West";
    }
    else if (direction == "se"){
        nr = r + 1;
        nc = c + 1;
        d = "South East";
    }
    else {
      // "sw"
        nr = r + 1;
        nc = c - 1;
        d = "South West";
    }

    
    if (status[r][c] != 9) {
      //setObservers(pc);
    }

    switch(mode){
        case 'u':{
        shared_ptr<Tile> t = dynamic_pointer_cast<Tile>(chambers[status[nr][nc]].cells[nr][nc]);
        if (t != nullptr && (t->getOccupied()) && 
        ((t->getObject()->getType() == "BA") || (t->getObject()->getType() == "WA") || (t->getObject()->getType() == "BD")
        || (t->getObject()->getType() == "WD") || (t->getObject()->getType() == "RH") || (t->getObject()->getType() == "PH"))) {
                        t->setOccupied(false);
						message += " uses " + t->getObject()->getType() + "."; 
                        shared_ptr<Potion> p = dynamic_pointer_cast<Potion>(chambers[status[nr][nc]].items[nr][nc]);
                        p->use(pc);
                        //remove potion after use
                        chambers[status[nr][nc]].items[nr].erase(nc);
            }
            //else do nothing
            break;
                 }
        case 'm':{
        // check if the cell player moved to is: gold, stair, tile, doorway or passage
        message += " moves " + d;
            if (charStatus[nr][nc] == '.') {
                        shared_ptr<Tile> t = dynamic_pointer_cast<Tile>(chambers[status[nr][nc]].cells[nr][nc]);
                        pc->setChamber(t->getChamberNumber());
                        if(!t->getOccupied()) {
                          pc->setPos(nr, nc);
                          t->setOccupied(true);
                          t->setObject(pc);
                          //tile, move
                          if (charStatus[r][c] == '.') {
                            shared_ptr<Tile> pt = dynamic_pointer_cast<Tile>(chambers[status[r][c]].cells[r][c]);
                            pt->setOccupied(false);
                          } else if (charStatus[r][c] == '+') {
                            shared_ptr<Door> pd = dynamic_pointer_cast<Door>(chambers[status[r][c]].cells[r][c]);
                            pd->setOccupied(false);
                          }
                          message += ".";
                        } else if ((t->getObject()->getType() == "MH") || (t->getObject()->getType() == "Small") 
                          || (t->getObject()->getType() == "Normal")
                          || ((t->getObject()->getType() == "DH") && 
                          !checkForDragon(nr,nc))) {
                            pc->setPos(nr, nc);
                            t->setOccupied(true);
                            //gold, pickup
                            shared_ptr<Treasure> g = dynamic_pointer_cast<Treasure>(chambers[status[nr][nc]].items[nr][nc]);
                            g->pickup(pc);
                            //pc->addGold(g->getAmount());
                            chambers[status[nr][nc]].items[nr].erase(nc);
                            //t->setObject(pc);
                            
                            if (charStatus[r][c] == '.') {
                            shared_ptr<Tile> pt1 = dynamic_pointer_cast<Tile>(chambers[status[r][c]].cells[r][c]);
                            pt1->setOccupied(false);
                          } else if (charStatus[r][c] == '+') {
                            shared_ptr<Door> pd1 = dynamic_pointer_cast<Door>(chambers[status[r][c]].cells[r][c]);
                            pd1->setOccupied(false);
                          }
                          message += " and picked up treasure.";
                        } else if (t->getObject()->getType() == "stairs") {
                           message += " and moves to the next floor.";
                            //generate new floor
                              level = level + 1;
                              if (level <= 5) {
								  reset(0);
                                generate();
                              } else {
                                int score = pc->getGold();
                                message += " finishes the game with score: " + to_string(score) + ".";
                                end = true;
                              }
                              //win
                        }
            } else if (charStatus[nr][nc] == '+') {
                      //doorway, move
                      shared_ptr<Door> d = dynamic_pointer_cast<Door>(chambers[status[nr][nc]].cells[nr][nc]);
                          pc->setPos(nr, nc);
                          pc->setChamber(d->getChamberNumber());
                          d->setOccupied(true);
                          //d->setObject(pc);
                           shared_ptr<Tile> dd = dynamic_pointer_cast<Tile>(chambers[status[nr][nc]].cells[nr][nc]);
                          //dd->setObject(pc);
                          if (charStatus[r][c] == '.') {
                            shared_ptr<Tile> pt2 = dynamic_pointer_cast<Tile>(chambers[status[r][c]].cells[r][c]);
                            pt2->setOccupied(false);
                          } else if (charStatus[r][c] == '#') {
                            passages[r][c]->setOccupied(false);
                          }   
                          message += "+";
            } else if (charStatus[nr][nc] == '#') {
                      //passage, move
                          pc->setPos(nr, nc);
                          passages[nr][nc]->setOccupied(true);
                      if (status[r][c] != 9) {
                         shared_ptr<Door> d2 = dynamic_pointer_cast<Door>(chambers[status[r][c]].cells[r][c]);
                         d2->setOccupied(false);
                      } else {
                        //unoccupy passage
                          //shared_ptr<Passage> pd2 = dynamic_pointer_cast<Passage>(chambers[status[r][c]].cells[r][c]);
                        passages[r][c]->setOccupied(false);
                      }
                      message += "#";
            }
                  //else do nothing 
                  message += ".";
            break;}
        case 'a':{
          if (charStatus[nr][nc] == '.')  {
                for (auto & enemy : chambers[pc->getChamberNumber()].enemies){
        	        if ((enemy->getRow() == nr) && (enemy->getCol() == nc)) {
                        int hp = enemy->getHP();
                        pc->attack(enemy);
                        message += " attacks " + enemy->getType() + " and " + 
                            enemy->getType() + "'s HP drops from " + to_string(hp) + " to " + to_string(enemy->getHP()) + "."; 
                    }
                }
          } 
            break;
        }
    }
    if (pc->getType() == "Troll") {
        pc->setHP(5);
    }

    /*
    for (auto & enemy : chambers[pc->getChamberNumber()].enemies){
        enemy->attach(pc);
    }
    */

    for (auto & chmbr : chambers){
        for (int i = 0; i < chmbr.enemies.size(); ++i){
            shared_ptr<Enemy> enemy = chmbr.enemies[i];
            if (enemy->isDead()){
          // drop gold if merchant and human
          //player gain gold automatically otherwise
                  if ((enemy->getType() == "Human") || (enemy->getType() == "Merchant")) {
                      int r = enemy->getRow();
                      int c = enemy->getCol();
                      shared_ptr<Tile> t = dynamic_pointer_cast<Tile>(chambers[status[r][c]].cells[r][c]);
                      shared_ptr<MerchantHoard> mh = make_shared<MerchantHoard>(r,c,status[r][c]);
                      if (chambers[status[r][c]].items.count(r) == 0) {
                          map<int, shared_ptr<Item>> tt;
                          tt.insert(pair<int,shared_ptr<MerchantHoard>>(c, mh));
                          chambers[status[r][c]].items[r] = tt; 
                        }
                      else {
                          chambers[status[r][c]].items[r].emplace(c, mh);
                      }
                      t->setObject(mh);
                  }
                  else if (enemy->getType() == "Dragon") {
                      shared_ptr<Dragon> dr = dynamic_pointer_cast<Dragon>(enemy);
                  }
                  else {
                      //srand(time(NULL));
                      int g = rand() % 2 + 1;
                      pc->addGold(g);
                  }
                  
                  if (pc->getType() == "Goblin") {
                      pc->addGold(5);
                  }
                  message += " PC has slain the " + enemy->getType();
                  chmbr.enemies.erase(chmbr.enemies.begin() + i);
            }
        }
    } 

     if (pc->isDead()) {
        message = "Player has been slain";
        end = true;
      }

    for (auto & chmbr : chambers){
        for (auto & enemy : chmbr.enemies){
            if (enemy->getChamberNumber() == pc->getChamberNumber() && abs(enemy->getCol() - pc->getCol()) <= 1 && abs(enemy->getRow() - pc->getRow()) <= 1){
                if (enemy->getType() != "Merchant") enemy->attack(pc);
                else{
                    shared_ptr<Merchant> m = dynamic_pointer_cast<Merchant>(enemy);
                    if (m->getHostile()) enemy->attack(pc);
                }
            }
            else if(enemy->getType()!="Dragon") randomMove(enemy);
       }
    }
}

std::vector<std::vector<int>> Floor::getStatus(){
  return status;
}

void Floor::reset(int flag){
    // flag = 0 : move to next level reset, flag = 1: restart game
    if (flag){
        pc.reset();
    }
    else{
        pc->resetStat();

        vector<shared_ptr<Tile>> pos;
        srand(time(NULL));
        int ch = rand() % 5;
        for (auto & it : chambers[ch].cells){
            for (auto & t : it.second){
                if (t.second->getType() == "tile"){
                    std::shared_ptr<Tile> oo = std::dynamic_pointer_cast<Tile> (t.second);
                    if (!oo->getOccupied()) pos.emplace_back(oo);
                }
            }
        }
        int aha = rand() % pos.size();
        int x = pos[aha]->getRow();
        int y = pos[aha]->getCol();
        pc->setPos(x, y);
    }

    message.clear();

    for (auto & r: passages){
        for (auto & c : r.second){
            c.second->setOccupied(false);
        }
    }

    for (auto & chmbr : chambers){
        chmbr.enemies.clear();
        for (auto & r : chmbr.items){
            r.second.clear();
        }
        chmbr.items.clear();
        chmbr.stairs = nullptr;

        for (auto & r : chmbr.cells){
            for (auto & c : r.second){
                if (c.second->getType() == "door"){
                    shared_ptr<Door> t = dynamic_pointer_cast<Door>(c.second);
                    t->setOccupied(false);
                }
                else if (c.second->getType() == "tile"){
                    shared_ptr<Tile> t = dynamic_pointer_cast<Tile>(c.second);
                    t->setOccupied(false);
                }
                else if (c.second->getType() == "stair"){
                    r.second.erase(c.second->getCol());
                }
            }
        }
    }
}


void Floor::setEnemyStop(){
	enemyStop = !enemyStop;
}

void Floor::spawnDragon(int x, int y, int cn, shared_ptr<DragonHoard> dh){
	// 0-no,1-so,2-ea,3-we,4-ne,5-nw,6-se,7-sw
    vector<shared_ptr<Tile>> ts;
    for (int i = x - 1; i < x + 2; ++i){
        for (int j = y - 1; j < y + 2; ++j){
            if (! (i == x && j == y) && status[i][j] == cn && charStatus[i][j] == '.'){
                shared_ptr<Tile> w1 = dynamic_pointer_cast<Tile>(chambers[cn].cells[i][j]);
                if (!w1->getOccupied()) ts.push_back(w1);
            }
        }
    }
    
    int pos = rand() % ts.size();
    int r = ts[pos]->getRow(), c = ts[pos]->getCol();
    shared_ptr<Dragon> dr = make_shared<Dragon>(r,c,cn,dh);
    chambers[cn].enemies.push_back(dr);
    ts[pos]->setOccupied(true);
    ts[pos]->setObject(dr);
}

void Floor::resetTile(int x, int y, int chamber){
    shared_ptr<Tile> t = dynamic_pointer_cast<Tile>(chambers[chamber].cells[x][y]);
	t->setOccupied(false);
    t->setObject(nullptr);
}   

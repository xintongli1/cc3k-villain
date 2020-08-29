#include "floorDisplay.h"
#include "wall.h"
#include "tile.h"
#include "door.h"
#include "passage.h"
#include <memory>
#include <sstream>
#include <iomanip>

using namespace std;

FloorDisplay::FloorDisplay(std::shared_ptr<Floor> f): win{newwin(25, 79, 10, 20)}, pcInfo{newwin(6, 79, 40, 20)}, floor{f}{
    box(win, 0, 0);
    for (int i = 1; i < 24; ++i){
        for (int j = 1; j < 78; ++j){
            std::string str {f->charStatus[i][j]};
            const char * t = str.data();
            mvwprintw(win, i, j, t);
        }
    }

	wrefresh(win);

	ostringstream ss;
	ss << "Race: " << f->pc->getType() << " Gold: 0" << setw(50) << "Floor " << to_string(f->level) << endl << "HP: 125" << endl << "Atk: 25" << endl << "Def: 25" << endl << "Action: " << endl;
	mvwprintw(pcInfo, 0, 0, ss.str().data());

    wrefresh(pcInfo);

	//keypad(win, true);

}


FloorDisplay::~FloorDisplay(){
	delwin(win); delwin(pcInfo);
}

void FloorDisplay::display() {
    // display pc
    std::string str {};
    const char * t = "@";
    mvwprintw(win, floor->pc->getRow(), floor->pc->getCol(), t);

    for (auto & r : floor->passages){
        for (auto & c : r.second){
            if (!c.second->getOccupied())
                mvwprintw(win, c.second->getRow(), c.second->getCol(), "%c ", '#');
            else
                mvwprintw(win, c.second->getRow(), c.second->getCol(), "%c ", '@');
        }
    }


    for (auto & chmbr : floor->chambers){
         // display Cells
        for (auto & r : chmbr.cells){
            for (auto & c : r.second){
                if (c.second->getType() == "wall"){
                    shared_ptr<Wall> t = dynamic_pointer_cast<Wall>(c.second);
                    str = t->getWallType();
                    mvwprintw(win, t->getRow(), t->getCol(), str.data());
                }
                else if (c.second->getType() == "tile"){
                    shared_ptr<Tile> t = dynamic_pointer_cast<Tile>(c.second);
                    if (t->getOccupied() == false){
                        str = '.';
                        mvwprintw(win, t->getRow(), t->getCol(), str.data());
                    }
                }
                else if (c.second->getType() == "door"){
                    shared_ptr<Door> t = dynamic_pointer_cast<Door>(c.second);
                    if (t->getOccupied() == false){
                        str = '+';
                        mvwprintw(win, t->getRow(), t->getCol(), str.data());
                    }
                }
                else {// passage
                    shared_ptr<Passage> t = dynamic_pointer_cast<Passage>(c.second);
                    if (t->getOccupied() == false){
                        str = '#';
                        mvwprintw(win, t->getRow(), t->getCol(), str.data());
                    }
                }

            }
        }


        // display enemies
        for (auto & e : chmbr.enemies){
            if (!e->isDead()){
                str = e->getChar();
                const char * t = str.data();
                mvwprintw(win, e->getRow(), e->getCol(), t);
            }
        }

        // display items
        for (auto & i: chmbr.items){
            for (auto & j : i.second){
                if (j.second->getType() == "Small" || j.second->getType() == "Normal" || j.second->getType() == "DH" || j.second->getType() == "MH"){
                    mvwprintw(win, j.second->getRow(), j.second->getCol(), "G");
                }
                else{ // potions
                    mvwprintw(win, j.second->getRow(), j.second->getCol(), "P");
                }
            }
        }

        if (chmbr.stairs != nullptr){
            mvwprintw(win, chmbr.stairs->getRow(), chmbr.stairs->getCol(), "\\");
        }
    }

	std::ostringstream ss {};
    ss << "Race: " << floor->pc->getType() << " Gold: " << floor->pc->getGold() << setw(50) << "Floor " << to_string(floor->level) << endl
        << "HP: " << floor->pc->getHP() << endl
        << "Atk: " << floor->pc->getAtk() << endl
        << "Def: " << floor->pc->getDef() << endl
        << "Action: " << floor->message << endl;
    mvwprintw(pcInfo, 0, 0, ss.str().data());

    wrefresh(win);
    wrefresh(pcInfo);

}


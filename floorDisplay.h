#ifndef _FLOORDISPLAY_H_
#define _FLOORDISPLAY_H_

#include "floor.h"
#include <ncurses.h>
using namespace std;

class FloorDisplay{
    WINDOW * win;
	WINDOW * pcInfo; // HP, ATK, ...
    std::shared_ptr<Floor> floor;

    public:
    FloorDisplay(std::shared_ptr<Floor> floor);
    void display();
	~FloorDisplay();
};
#endif


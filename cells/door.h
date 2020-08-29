#ifndef _DOOR_H_
#define _DOOR_H_
#include "cell.h"
class Door: public Cell{
	bool occupied;
    public:
        Door(const int r, const int c, const int ch);
		bool getOccupied();
		void setOccupied(bool);
};

#endif

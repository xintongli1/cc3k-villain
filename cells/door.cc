#include "door.h"

Door::Door (const int r, const int c, const int ch):
    Cell{r, c, "door", ch}, occupied{false}{}

bool Door::getOccupied(){
	return occupied;
}

void Door::setOccupied(bool b){
	occupied = b;
}

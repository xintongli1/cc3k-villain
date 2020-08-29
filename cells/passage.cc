#include "passage.h"

Passage::Passage(const int r, const int c, const int ch ):
    Cell{r, c, "passage", ch}, occupied{false}{}

bool Passage::getOccupied(){
	return occupied;
}

void Passage::setOccupied(bool b){
	occupied = b;
}

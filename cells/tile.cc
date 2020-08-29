#include "tile.h"

Tile::Tile(const int r, const int c, const int ch):
    Cell{r, c, "tile", ch}, occupied{false}{}

bool Tile::getOccupied(){
	return occupied;
}

void Tile::setOccupied(bool b){
	occupied = b;
}

std::shared_ptr<Object> Tile::getObject(){
	return object;
}

void Tile::setObject(std::shared_ptr<Object> o){
	object = o;
}

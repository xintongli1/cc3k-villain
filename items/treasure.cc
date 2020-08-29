#include "treasure.h"
Treasure::Treasure(const int row, const int col, const std::string type, const int chamber, int amount) :
Item{row, col, type, chamber, amount}{}

Treasure::~Treasure(){
}


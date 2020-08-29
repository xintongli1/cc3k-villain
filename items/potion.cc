#include "potion.h"

Potion::Potion(const int row, const int col, const std::string type, const int chamber, int amount) :
    Item{row, col, type, chamber, amount} {}

Potion::~Potion() {};


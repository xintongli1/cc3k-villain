#include "item.h"

Item::Item(const int row, const int col, const std::string type, const int chamber, int a) :Object{row, col, type, chamber}, amount{a} {}

int Item::getAmount() const{
    return amount;
}

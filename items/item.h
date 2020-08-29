#ifndef _ITEM_H_
#define _ITEM_H_
#include <iostream>
#include "object.h"
#include "player.h"

class Item: public Object{
    int amount;
public:
  Item(const int row, const int col, const std::string type, const int chamber, int a);
  int getAmount() const;
};
#endif

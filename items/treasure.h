#ifndef _TREASURE_H_
#define _TREASURE_H_
#include <memory>
#include "item.h"
class Treasure: public Item {
    public:
        Treasure(const int row, const int col, const std::string type, const int chamber, int amount);
        ~Treasure();
        virtual void pickup(std::shared_ptr<Player> p)=0;
};

#endif

#ifndef _SMALL_H_
#define _SMALL_H_
#include "treasure.h"
class Small: public Treasure {
    public:
        Small(const int row, const int col, const int chamber);
        void pickup(std::shared_ptr<Player> p) override;
};

#endif

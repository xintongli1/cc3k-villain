#ifndef _NORMAL_H_
#define _NORMAL_H_
#include "treasure.h"
class Normal: public Treasure {
    public:
        Normal(const int row, const int col, const int chamber);
        void pickup(std::shared_ptr<Player> p) override;
};

#endif

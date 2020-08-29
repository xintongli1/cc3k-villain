#ifndef _DH_H_
#define _DH_H_
#include "treasure.h"
class DragonHoard: public Treasure {
    public:
        DragonHoard(const int row, const int col, const int chamber);
        void pickup(std::shared_ptr<Player> p) override;
};

#endif

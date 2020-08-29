#ifndef _MH_H_
#define _MH_H_
#include "treasure.h"
class MerchantHoard: public Treasure {
    public:
        MerchantHoard(const int row, const int col, const int chamber);
        void pickup(std::shared_ptr<Player> p) override;
};

#endif

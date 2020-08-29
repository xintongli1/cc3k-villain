#ifndef _RH_H_
#define _RH_H_
#include "potion.h"
class RH: public Potion{
    public:
        RH(const int row, const int col, const int chamber);
        void use(std::shared_ptr<Player> p) override;
        //void use(Player* p) override;
};

#endif

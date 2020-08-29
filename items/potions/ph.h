#ifndef _PH_H_
#define _PH_H_
#include "potion.h"
class PH: public Potion{
    public:
        PH(const int row, const int col, const int chamber);
        void use(std::shared_ptr<Player> p) override;
        //void use(Player* p) override;
};

#endif

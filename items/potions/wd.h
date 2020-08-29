#ifndef _WD_H_
#define _WD_H_
#include "potion.h"
class WD: public Potion{
    public:
        WD(const int row, const int col, const int chamber);
        void use(std::shared_ptr<Player> p) override;
        //void use(Player* p) override;
};

#endif

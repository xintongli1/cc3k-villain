#ifndef _WA_H_
#define _WA_H_
#include "potion.h"
class WA: public Potion{
    public:
        WA(const int row, const int col, const int chamber);
        void use(std::shared_ptr<Player> p) override;
        //void use(Player* p) override;
};

#endif

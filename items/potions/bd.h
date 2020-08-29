#ifndef _BD_H_
#define _BD_H_
#include "potion.h"
class BD: public Potion{
    public:
        BD(const int row, const int col, const int chamber);
        void use(std::shared_ptr<Player> p) override;
        //void use(Player* p) override;
};

#endif

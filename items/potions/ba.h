#ifndef _BA_H_
#define _BA_H_
#include "potion.h"
class BA: public Potion{
    public:
        BA(const int row, const int col, const int chamber);
        void use(std::shared_ptr<Player> p) override;
};

#endif

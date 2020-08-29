#ifndef _POTION_H_
#define _POTION_H_
#include "item.h"
class Potion: public Item{
  bool known;
    public:
        Potion(const int row, const int col, const std::string type, const int chamber, int amount);
        virtual ~Potion() = 0;
        virtual void use(std::shared_ptr<Player> p)=0;
};

#endif

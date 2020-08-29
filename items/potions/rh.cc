#include "rh.h"

RH::RH(const int row, const int col, const int chamber) :
Potion{row, col, "RH", chamber, 10} {}

void RH::use(std::shared_ptr<Player>p) {
  if (p->getType() == "drow") {
    p->setHP(10*1.5);
  } else {
    p->setHP(10);
  }
}

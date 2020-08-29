#include "ph.h"

PH::PH(const int row, const int col, const int chamber) :
Potion{row, col, "PH", chamber, -10} {}

void PH::use(std::shared_ptr<Player>p) {
  if (p->getType() == "drow") {
    p->setHP(-10*1.5);
  } else {
    p->setHP(-10);
  }
}


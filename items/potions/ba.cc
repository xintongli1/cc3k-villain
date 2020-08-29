#include "ba.h"

BA::BA(const int row, const int col, const int chamber) :
Potion{row, col, "BA", chamber, 5} {}

void BA::use(std::shared_ptr<Player>p) {
  if (p->getType() == "drow") {
    p->setAtk(5*1.5);
  } else {
    p->setAtk(5);
  }
}

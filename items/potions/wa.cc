#include "wa.h"

WA::WA(const int row, const int col, const int chamber) :
Potion{row, col, "WA", chamber, -5} {}

void WA::use(std::shared_ptr<Player>p) {
  if (p->getType() == "drow") {
    p->setAtk(-5*1.5);
  } else {
    p->setAtk(-5);
  }
}


#include "bd.h"

BD::BD(const int row, const int col, const int chamber) :
Potion{row, col, "BD", chamber, 5} {}

void BD::use(std::shared_ptr<Player>p) {
  if (p->getType() == "drow") {
    p->setDef(5*1.5);
  } else {
    p->setDef(5);
  }
}

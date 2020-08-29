#include "wd.h"

WD::WD(const int row, const int col, const int chamber) :
Potion{row, col, "WD", chamber, -5} {}

void WD::use(std::shared_ptr<Player>p) {
  if (p->getType() == "drow") {
    p->setDef(-5*1.5);
  } else {
    p->setDef(-5);
  }
}

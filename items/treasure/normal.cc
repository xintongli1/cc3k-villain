#include "normal.h"
 Normal::Normal(const int row, const int col, const int chamber):
 Treasure{row, col, "Normal", chamber, 2} {}

void Normal::pickup(std::shared_ptr<Player> p) {
  p->addGold(2);
}

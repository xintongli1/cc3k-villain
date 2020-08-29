#include "small.h"
 Small::Small(const int row, const int col, const int chamber):
 Treasure{row, col, "Small", chamber, 1} {}

void Small::pickup(std::shared_ptr<Player> p) {
  p->addGold(1);
}

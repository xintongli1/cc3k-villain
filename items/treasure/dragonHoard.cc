#include "dragonHoard.h"
 DragonHoard::DragonHoard(const int row, const int col, const int chamber):
 Treasure{row, col, "DH", chamber, 6} {}

void DragonHoard::pickup(std::shared_ptr<Player> p) {
  p->addGold(6);
}

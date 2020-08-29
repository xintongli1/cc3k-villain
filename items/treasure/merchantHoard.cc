#include "merchantHoard.h"
 MerchantHoard::MerchantHoard(const int row, const int col, const int chamber):
 Treasure{row, col, "MH", chamber, 4} {}

void MerchantHoard::pickup(std::shared_ptr<Player> p) {
  p->addGold(4);
}

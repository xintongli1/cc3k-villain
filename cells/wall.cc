#include "wall.h"

Wall::Wall (const int r, const int c, const int ch, const char wt):
    Cell{r, c, "wall", ch}, wallType{wt}{}

char Wall::getWallType() const{
    return wallType;
}

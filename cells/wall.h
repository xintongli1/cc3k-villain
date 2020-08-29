#ifndef _WALL_H_
#define _WALL_H_
#include "cell.h"
class Wall : public Cell{
	char wallType;
    public:
        Wall (const int r, const int c, const int ch, const char wt);
		char getWallType() const;
};

#endif

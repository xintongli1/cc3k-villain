#ifndef _TILE_H_
#define _TILE_H_
#include "cell.h"
#include <memory>

class Tile: public Cell{
	bool occupied;
	std::shared_ptr<Object> object;
    public:
        Tile (const int r, const int c, const int ch);
		bool getOccupied();
		void setOccupied(bool);
		std::shared_ptr<Object> getObject();
		void setObject(std::shared_ptr<Object>);
};

#endif


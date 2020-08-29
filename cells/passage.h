#ifndef _PASSAGE_H_
#define _PASSAGE_H_
#include "cell.h"

class Passage : public Cell{
	bool occupied;
    public:
        Passage(const int r, const int c, const int ch = 5);
		bool getOccupied();
		void setOccupied(bool);
};


#endif


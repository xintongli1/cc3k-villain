#ifndef _CELL_H_
#define _CELL_H_

#include "object.h"

class Cell : public Object{
	public:
		Cell(const int r, const int c, const std::string & t, const int ch);
};

#endif

/*
	extra private field:
	tile: bool occupied, shared_ptr<Object>
	passage: bool occupied
	door bool occupied
*/

#include "object.h"
using namespace std;

Object::Object(const int r, const int c, const std::string & t, const int ch):
    row{r}, col{c}, type{t}, chamber{ch} {}

int Object::getRow() const{
    return row;
}

int Object::getCol() const{
    return col;
}

std::string Object::getType() const {
    return type;
}

int Object::getChamberNumber() const{
    return chamber;
}

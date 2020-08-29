#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>

class Object{
    protected:
        int row, col;
        std::string type;
        int chamber; // the chamber it belongs to

    public:
        Object(const int r, const int c, const std::string & t, const int ch);
        virtual ~Object()=default;
        int getRow() const;
        int getCol() const;
        std::string getType() const;
        int getChamberNumber() const;

};


#endif

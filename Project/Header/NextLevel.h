#ifndef NEXTLEVEL_H
#define NEXTLEVEL_H

#include "rect.h"
#include "globals.h"
#include <string>

class NextLevel : public Rectangle{
public:
	NextLevel(){}
	NextLevel(Rectangle r, std::string destination):
		Rectangle(r.getLeft(), r.getTop(), r.getWidth(), r.getHeight()),
		_destination(destination)
	{}

	const inline Rectangle getRect() const{return this->getRect();}
	const inline std::string getDest() const { return this-> _destination;}

private:
	std::string _destination;
};


#endif

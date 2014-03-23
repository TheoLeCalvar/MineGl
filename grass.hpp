#ifndef GRASS_H
#define GRASS_H

#include "cube.hpp"

class Grass: public Cube
{
public:
	Grass(unsigned char visibility = 0);
	~Grass(){}
	
	virtual void display();
	virtual cube_type getType(){return GRASS;}
};

#endif
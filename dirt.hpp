#ifndef DIRT_H
#define DIRT_H

#include "cube.hpp"

#define DIRT_UMIN 32.0f/64.0f
#define DIRT_UMAX 47.0f/64.0f
#define DIRT_VMIN 0.0f/64.0f
#define DIRT_VMAX 15.0f/64.0f

class Dirt: public Cube
{
public:
	Dirt(unsigned char visibility = 0);
	~Dirt(){}
	
	virtual void display();
};

#endif
#ifndef STONE_H
#define STONE_H

#include "cube.hpp"

#define STONE_UMIN 16.0f/64.0f
#define STONE_UMAX 31.0f/64.0f
#define STONE_VMIN 16.0f/64.0f
#define STONE_VMAX 31.0f/64.0f

class Stone: public Cube
{
public:
	Stone(GLfloat size = 1.0f, char visibility = 0);
	~Stone(){}
	
	virtual void display();
};

#endif
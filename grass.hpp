#ifndef GRASS_H
#define GRASS_H

#include "cube.hpp"

class Grass: public Cube
{
public:
	Grass(GLfloat size = 1.0f, char visibility = 0);
	~Grass(){}
	
	virtual void display();
};

#endif
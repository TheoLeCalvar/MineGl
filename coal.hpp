#ifndef COAL_H
#define COAL_H

#include "cube.hpp"

#define COAL_UMIN 0.0f
#define COAL_UMAX 15.0f/64.0f
#define COAL_VMIN 16.0f/64.0f
#define COAL_VMAX 31.0f/64.0f 

class Coal: public Cube
{
public:
	Coal(GLfloat size = 1.0f, char visibility = 0);
	~Coal(){}
	
	virtual void display();
};

#endif
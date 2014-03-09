#ifndef WATER_H
#define WATER_H

#include "cube.hpp"


class Water: public Cube
{
private:
	unsigned char _frame;
	int 	_x;
	int 	_y;
	int 	_z;
public:
	Water(unsigned char visibility = 0);
	~Water(){}
	
	virtual void display();
	void 	setPosition(int x, int y, int z){_x = x; _y = y; _z = z;}
};

#endif
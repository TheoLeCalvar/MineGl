#ifndef WATER_H
#define WATER_H

#include "cube.hpp"


class Water: public Cube
{
private:
	static unsigned char _frame;

public:
	Water(unsigned char visibility = 0);
	~Water(){}
	
	virtual void display();
	virtual cube_type getType(){return WATER;}
	static void inc();
};

#endif

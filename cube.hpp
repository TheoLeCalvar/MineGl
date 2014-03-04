#ifndef CUBE_H
#define CUBE_H

#include "objet.hpp"

typedef enum {
	FRONT = 1,
	RIGHT = 2,
	BACK  = 4,
	LEFT  = 8,
	TOP   = 16,
	BOT   = 32
} side;

class Cube:public Objet
{
protected:
	static GLfloat  _points[];
	static GLfloat  _normals[];
	char 			_visibility;

public:
	Cube(GLfloat size = 1.0f, char visibility = 0);
	virtual ~Cube(){}

	void setVisibility(char visibility){_visibility = visibility;}
	void setVisibility(side s, bool b);
	char getVisibility(){return _visibility;}
	char getVisibility(side s){return _visibility & s;}

	virtual void display();
};

#endif
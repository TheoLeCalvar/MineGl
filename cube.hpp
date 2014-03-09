#ifndef CUBE_H
#define CUBE_H

#include "renderer.hpp"
#include <SOIL/SOIL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

typedef enum {
	FRONT = 1,
	RIGHT = 2,
	BACK  = 4,
	LEFT  = 8,
	TOP   = 16,
	BOT   = 32,
	TRANSPARENT = 64
} side;

class Cube
{
public:
 	static GLuint   _texId[];

protected:
	static Renderer *      _renderer;
	static GLfloat  _points[];
	static GLfloat  _normals[];
	unsigned char	_visibility;

public:
	Cube(unsigned char visibility = 0);
	virtual ~Cube(){}

	static  void setRenderer(Renderer * r){_renderer = r;}
	static  void loadTexture();

	bool isTransparent(){return (_visibility & TRANSPARENT) == TRANSPARENT;}
	void setVisibility(char visibility){_visibility = visibility;}
	void setVisibility(side s, bool b);
	unsigned char getVisibility(){return _visibility;}
	unsigned char getVisibility(side s){return _visibility & s;}

	virtual void display();
};

#endif
#ifndef WORLD_H
#define WORLD_H

#define WORLDSIZEX 64
#define WORLDSIZEY 64
#define WORLDSIZEZ 64

#ifdef __APPLE__
//gestion de la souris
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <vector>
#include "renderer.hpp"
#include "cube.hpp"
#include "dirt.hpp"
#include "grass.hpp"
#include "stone.hpp"
#include "coal.hpp"
#include "dirt.hpp"

class World
{
private:
	Renderer * 				_renderer;
	std::vector<Cube *> 	_blocs;

public:
	World(Renderer * renderer);
	~World();

	void draw();
	
};


#endif
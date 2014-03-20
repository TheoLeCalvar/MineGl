#ifndef WORLD_H
#define WORLD_H

#define WORLDSIZEX 129
#define WORLDSIZEY 129
#define WORLDSIZEZ 128
#define WATER_LEVEL 50

#define XYZ(x, y, z) ((x) + (WORLDSIZEX * (y)) + (WORLDSIZEY * WORLDSIZEX * (z)))
#define XY(x, y) ((x) + ((y) * WORLDSIZEX))

class Player;

#ifdef __APPLE__
//gestion de la souris
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>
#include <vector>
#include "renderer.hpp"
#include "cube.hpp"
#include "dirt.hpp"
#include "grass.hpp"
#include "stone.hpp"
#include "coal.hpp"
#include "dirt.hpp"
#include "water.hpp"

class World
{
private:
	Renderer * 					_renderer;
	std::vector<Cube *> 		_blocs;
	std::vector<unsigned int> 	_height;

	//passer par un chunk pour découper le monde en plus petites listes d'affichage 
	GLuint 						_listId;


	Player * 					_player;

public:
	World(Renderer * renderer);
	~World();

	void 			draw();
	void 			touche(int key, int action);
	unsigned int	hauteur(int x, int y);
	bool			empty(float x, float y, float z);
	bool 			empty(Vect3D p);

private:
	void 			genHeight();
	void 			calcVisibility();
	void 			sun();
};


#endif
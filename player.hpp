#ifndef PLAYER_H
#define PLAYER_H


#include "camera.hpp"
#include "vect3D.hpp"
#include "world.hpp"

class Player: public Camera
{
private:
	World * 	_world;
	bool 		_fly;
	Vect3D 		_v;
public:
	Player();
	~Player();

	void 	toucheJoueur(int key, int scancode, int action, int mods);
	
};


#endif
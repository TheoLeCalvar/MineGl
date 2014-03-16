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
	Vect3D 		_position;
	bool 		_jump;

public:
	Player(World * w);
	Player(GLfloat x, GLfloat y, GLfloat z);
	virtual ~Player();

	void 	toucheJoueur(int key, int scancode, int action, int mods);
	GLfloat  getPositionX(){return _position[0];}
	GLfloat  getPositionY(){return _position[1];}
	GLfloat  getPositionZ(){return _position[2];}

protected:
	virtual void 	move();
	
};


#endif
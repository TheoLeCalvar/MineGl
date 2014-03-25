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
	bool 		_jump;
	bool		_espace_presse;

	static Vect3D _gravity;

public:
	Player(World * w);
	Player(GLfloat x, GLfloat y, GLfloat z);
	virtual ~Player();

	void 	 toucheJoueur(int key, int action);
	GLfloat  getPositionX(){return _eye[0];}
	GLfloat  getPositionY(){return _eye[1];}
	GLfloat  getPositionZ(){return _eye[2];}
	void	 go(Vect3D v){_eye = v;}

protected:
	virtual void 	move();

private:
	void spawn();
	
};


#endif
#ifndef LUCIOLE_H
#define LUCIOLE_H

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include "vect3D.hpp"
#include "world.hpp"
#include "modele.hpp"

#define LUCIOLE_HEIGHT 0.10f
#define LUCIOLE_WIDTH  0.10f
#define LUCIOLE_LENGHT 0.30f

#define SQRT3 0.57735f

class Luciole
{
	static int  _NbLucioles;
	World * 	_world;
	int 		_id;

	Vect3D 		_pos;
	GLdouble 	_theta;
	GLdouble 	_phi;

	GLdouble 	_thetaCible;
	GLdouble 	_thetaOrig;
	char 		_thetaFrame;

	GLdouble 	_phiCible;
	GLdouble 	_phiOrig;
	char 		_phiFrame;



	//wing angle
	GLdouble 	_alpha;
	char 		_frame;

	static GLfloat 	_body[];
	static GLubyte 	_bodyIndices[];
	static GLfloat 	_wing[];
	static GLubyte 	_wingIndices[];
	// static GLfloat 	_light[];
	// static GLubyte	_lightIndices[];

	static Modele * _light;


public:
	Luciole(World * w, const Vect3D &pos, GLfloat theta = 0.0f, GLfloat phi = 0.0f);
	Luciole(World *);
	~Luciole();
	

	void draw();
	void AI();
	Vect3D getPos();

private:
	void spawn();
};



#endif

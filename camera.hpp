#ifndef CAMERA_H
#define CAMERA_H

#include "vect3D.hpp"

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif


class Camera
{
friend class Moteur;
private:
	Vect3D 	 eye;
	Vect3D   center;

	GLdouble phi;
	GLdouble theta;

	Vect3D  avant;
	Vect3D  gauche;
	Vect3D  haut;

	bool    avant_presse;
	bool	arriere_presse;
	bool	gauche_presse;
	bool	droite_presse;
	bool 	haut_presse;
	bool	bas_presse;

	GLdouble vitesse;


private:
	Camera(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ);
	~Camera(){}

	void 	move();
	void 	go(GLdouble x, GLdouble y, GLdouble z);
	void 	vectorFromAngle();
	void 	display();
	
};

#endif
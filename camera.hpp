#ifndef CAMERA_H
#define CAMERA_H

#include "vect3D.hpp"


#include <GLFW/glfw3.h>
#ifdef __APPLE__
	#include <ApplicationServices/ApplicationServices.h>
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif


class Camera
{
private:
	static Camera * 	_activeCamera;

protected:
	Vect3D 	 _eye;
	Vect3D   _center;

	GLdouble _phi;
	GLdouble _theta;

	Vect3D  _avant;
	Vect3D  _gauche;
	Vect3D  _haut;

	bool    _avant_presse;
	bool	_arriere_presse;
	bool	_gauche_presse;
	bool	_droite_presse;
	bool 	_haut_presse;
	bool	_bas_presse;

	GLdouble _vitesse;




protected:
	Camera(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ);
	virtual ~Camera(){}

	virtual void 	move();
	void 	go(GLdouble x, GLdouble y, GLdouble z);
	void 	vectorFromAngle();

public:
	virtual void display();

public:
	static void mouse_event(GLFWwindow *, double x, double y);
	static void setActiveCamera(Camera * c){_activeCamera = c;}
	
};

#endif
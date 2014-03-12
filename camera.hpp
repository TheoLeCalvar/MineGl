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




protected:
	Camera(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ);
	~Camera(){}

	void 	move();
	void 	go(GLdouble x, GLdouble y, GLdouble z);
	void 	vectorFromAngle();

public:
	void 	display();

public:
	static void mouse_event(GLFWwindow *, double x, double y);
	static void setActiveCamera(Camera * c){_activeCamera = c;}
	
};

#endif
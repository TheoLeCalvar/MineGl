#ifndef MOTEUR_H
#define MOTEUR_H

#ifdef __APPLE__
//gestion de la souris
	#include <ApplicationServices/ApplicationServices.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
#ifdef _WIN32
	#include <windows.h>
#endif
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <GLFW/glfw3.h>
#include <vector>
#include "objet.hpp"
#include "vect3D.hpp"
#include "renderer.hpp"
#include "world.hpp"
#include "camera.hpp"



#include "cube.hpp"
#include "grass.hpp"
#include "stone.hpp"
#include "coal.hpp"
#include "water.hpp"



class Moteur
{
private:
	static Moteur 	* 		_mot;
	static Renderer * 		_renderer;

	// std::vector<Objet *> 	m_listeObjet;
	GLFWwindow* 			_window;
	World * 				_world;



public:
	static Moteur * create();

	~Moteur();

	void 		start();

	void 		switch_light();
	void 		switch_cullface();
	void 		switch_wire();

	static void keyboard_handler(GLFWwindow *, int key, int scancode, int action, int mods);



private:

	Moteur();


	void 		lumiere();
	void 		init_scene();

};


#endif
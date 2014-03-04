#ifndef MOTEUR_H
#define MOTEUR_H

#ifdef __APPLE__
//gestion de la souris
	#include <ApplicationServices/ApplicationServices.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
#ifdef _WIN32
	#include <windows.h>
#endif
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

#include <GLFW/glfw3.h>
#include <vector>
#include "objet.hpp"
#include "vect3D.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "world.hpp"



#include "cube.hpp"
#include "grass.hpp"
#include "stone.hpp"
#include "coal.hpp"



class Moteur
{
private:
	static Moteur 	* 		mot;
	static Renderer * 		_renderer;

	// std::vector<Objet *> 	m_listeObjet;
	Camera * 			 	m_camera;
	GLFWwindow* 			m_window;
	World * 				_world;



public:
	static Moteur * create();

	~Moteur();

	void 		start();

	void 		enable(GLenum  cap);
	void 		disable(GLenum  cap);
	GLboolean 	isEnabled(GLenum  cap) const;

	void 		switch_blend();
	void 		switch_light();
	void 		switch_cullface();
	void 		switch_wire();

//	static void touche_handler(GLFWwindow * w, unsigned int key);
	static void keyboard_handler(GLFWwindow *, int key, int scancode, int action, int mods);
	static void mouse_event(GLFWwindow *, double x, double y);

	static void redimensionne(GLFWwindow* window, int width, int height);


private:

	Moteur();


	void 		lumiere();
	void 		init_scene();

};


#endif
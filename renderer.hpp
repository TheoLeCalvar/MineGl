#ifndef RENDERER_H
#define RENDERER_H


#ifdef __APPLE__
//gestion de la souris
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include "vect3D.hpp"
#include "vect4D.hpp"
#include <vector>

class Renderer
{
private:
	static Renderer * 		_instance;

	bool 					_useNormals;
	GLfloat 				_normX;
	GLfloat 				_normY;
	GLfloat 				_normZ;

	bool					_useTex;
	GLfloat					_texU;
	GLfloat					_texV;

	GLfloat 				_transX;
	GLfloat 				_transY;
	GLfloat 				_transZ;

	GLfloat *				_buffer;
	int						_bufSize;
	int 					_bufIndex;
	int						_verticesCount;

	bool 					_useMaterial;
	GLfloat 				_ambient[4];
	GLfloat					_diffuse[4];
	GLfloat					_specular[4];
	GLfloat					_emission[4];
	GLfloat 				_shininess;

	Renderer();
	~Renderer();

public:

	static Renderer * 	create();
	static void 		destroy();
	void 		clean();
	void 		reset();

	void 		addVertex(GLfloat x, GLfloat y, GLfloat z);
	void 		addVertex(GLfloat *v);
	void 		addVertexUV(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v);
	void 		addVertexUV(GLfloat * w, GLfloat u, GLfloat v);

	void 		setActiveTex(GLuint id);

	void 		setBlending(bool b);

	void 		setNormal(GLfloat x, GLfloat y, GLfloat z);
	void 		setNormal(GLfloat *v);
	void 		useNormals(bool);


	void 		setAmbient(GLfloat * v);
	void 		setAmbient(Vect4D<GLfloat> v);
	void 		setDiffuse(GLfloat * v);
	void 		setDiffuse(Vect4D<GLfloat> v);
	void 		setSpecular(GLfloat * v);
	void 		setSpecular(Vect4D<GLfloat> v);
	void 		setEmission(GLfloat * v);
	void 		setEmission(Vect4D<GLfloat> v);
	void 		setShininess(GLfloat v);
	void 		useMaterial(bool);

	void 		setTranslation(GLfloat x, GLfloat y, GLfloat z);
	void 		setTranslation(GLfloat * v);

	void 		display();


	
};


#endif

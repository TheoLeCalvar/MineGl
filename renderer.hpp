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

	Renderer();
	~Renderer();

public:

	static Renderer * 	create();
	static void 		destroy();
	void 		clean();

	void 		addVertex(GLfloat x, GLfloat y, GLfloat z);
	void 		addVertex(GLfloat *v);
	void 		addVertexUV(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v);
	void 		addVertexUV(GLfloat * w, GLfloat u, GLfloat v);

	void 		setNormal(GLfloat x, GLfloat y, GLfloat z);
	void 		useNormals(bool);

	void 		setTranslation(GLfloat x, GLfloat y, GLfloat z);
	void 		setTranslation(GLfloat * v);

	void 		display();


	
};


#endif
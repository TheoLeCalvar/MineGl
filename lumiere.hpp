#ifndef LUMIERE_H
#define LUMIERE_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


class Lumiere
{
	unsigned char 	m_number;
	GLfloat 		m_specular[4];
	GLfloat 		m_diffuse[4];
	GLfloat 		m_position[4];
	GLfloat 		m_spot_direction[3];
	GLfloat 		m_angle;



public:
	Lumiere(unsigned char number);
	~Lumiere();

	void setSpecular(GLfloat *v);
	void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void setDiffuse(GLfloat *v);
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void setPosition(GLfloat *v);
	void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	void setAngle(GLfloat a);
	void setSpotDirection(GLfloat *v);
	void setSpotDirection(GLfloat x, GLfloat y, GLfloat z);

	void enable();
	void disable();


	
};

#endif
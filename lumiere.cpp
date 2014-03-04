#include "lumiere.hpp"

Lumiere::Lumiere(unsigned char number){
	if (number < 8)
	{
		
	}
}
Lumiere::~Lumiere(){
	disable();
}

void Lumiere::setSpecular(GLfloat *v){
	m_specular[0] = v[0];
	m_specular[1] = v[1];
	m_specular[2] = v[2];
	m_specular[3] = v[3];

	glLightfv(GL_LIGHT0 + m_number, GL_SPECULAR, m_specular);
}
void Lumiere::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
	m_specular[0] = r;
	m_specular[1] = g;
	m_specular[2] = b;
	m_specular[3] = a;

	glLightfv(GL_LIGHT0 + m_number, GL_SPECULAR, m_specular);
}

void Lumiere::setDiffuse(GLfloat *v){
	m_diffuse[0] = v[0];
	m_diffuse[1] = v[1];
	m_diffuse[2] = v[2];
	m_diffuse[3] = v[3];

	glLightfv(GL_LIGHT0 + m_number, GL_DIFFUSE, m_diffuse);
}
void Lumiere::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
	m_diffuse[0] = r;
	m_diffuse[1] = g;
	m_diffuse[2] = b;
	m_diffuse[3] = a;

	glLightfv(GL_LIGHT0 + m_number, GL_DIFFUSE, m_diffuse);
}

void Lumiere::setPosition(GLfloat *v){
	m_position[0] = v[0];
	m_position[1] = v[1];
	m_position[2] = v[2];
	m_position[3] = v[3];

	glLightfv(GL_LIGHT0 + m_number, GL_POSITION, m_position);
}
void Lumiere::setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;
	m_position[3] = w;

	glLightfv(GL_LIGHT0 + m_number, GL_POSITION, m_position);
}

void Lumiere::setAngle(GLfloat a){
	m_angle = a;

	glLightf(GL_LIGHT0 + m_number, GL_SPOT_CUTOFF, m_angle);
}
void Lumiere::setSpotDirection(GLfloat *v){
	m_spot_direction[0] = v[0];
	m_spot_direction[1] = v[1];
	m_spot_direction[2] = v[2];

	glLightfv(GL_LIGHT0 + m_number, GL_SPOT_DIRECTION, m_spot_direction);
}
void Lumiere::setSpotDirection(GLfloat x, GLfloat y, GLfloat z){
	m_spot_direction[0] = x;
	m_spot_direction[1] = y;
	m_spot_direction[2] = z;

	glLightfv(GL_LIGHT0 + m_number, GL_SPOT_DIRECTION, m_spot_direction);
}

void Lumiere::enable(){
	glEnable(GL_LIGHT0 + m_number);
}

void Lumiere::disable(){
	glDisable(GL_LIGHT0 + m_number);
}
#include "objet.hpp"

GLuint Objet::m_texId = 0;
Renderer * Objet::_renderer = NULL;

Objet::Objet():
	m_translation(0.0f, 0.0f, 0.0f), 
	m_scale(1.0f, 1.0f, 1.0f),
	m_rotation_axe(0.0f, 0.0f, 1.0f), m_rotation_angle(0.0f),
	display_normale(false),
	m_ambient(0.2f, 0.2f, 0.2f, 1.0f), m_diffuse(0.8f, 0.8f, 0.8f, 1.0f), 
	m_specular(0.8f, 0.8f, 0.8f, 1.0f), m_emission(0.0f, 0.0f, 0.0f, 1.0f),
	m_shininess(1)
{
	if (!m_texId)
	{
		int width = 64, height = 64, channel = 0;
		unsigned char  * m_image;

		glActiveTexture(GL_TEXTURE0);
		m_image = SOIL_load_image("texture/textures.png", &width, &height, &channel, SOIL_LOAD_RGBA);
		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		SOIL_free_image_data(m_image);
	}
}

Objet::~Objet(){

}

void Objet::setTranslation(Vect3D v)
{
	m_translation.copy(v);
}

void Objet::setTranslation(GLdouble x, GLdouble y, GLdouble z)
{
	m_translation.set(x, y, z);
}

void Objet::setScale(Vect3D v)
{
	m_scale.copy(v);
}

void Objet::setScale(GLdouble x, GLdouble y, GLdouble z)
{
	m_scale.set(x, y, z);
}

void Objet::setRotation(Vect4D<GLdouble> v)
{
	m_rotation_angle = v[0];
	m_rotation_axe.set(v[1], v[2], v[3]);
}

void Objet::setRotation(GLdouble angle, GLdouble x, GLdouble y, GLdouble z){
	m_rotation_angle = angle;
	m_rotation_axe.set(x, y, z);
}

void Objet::setAmbient(Vect4D<GLfloat> v){
	m_ambient.copy(v);
}

void Objet::setDiffuse(Vect4D<GLfloat> v){
	m_diffuse.copy(v);
}

void Objet::setSpecular(Vect4D<GLfloat> v){
	m_specular.copy(v);
}

void Objet::setEmission(Vect4D<GLfloat> v){
	m_emission.copy(v);
}

void Objet::setShininess(GLfloat v){
	m_shininess = v;
}

void Objet::applyRotation(){
	glRotated(m_rotation_angle, m_rotation_axe[0], m_rotation_axe[1] , m_rotation_axe[2]);
}

void Objet::applyTranslation(){
	glTranslated(m_translation[0], m_translation[1], m_translation[2]);
}

void Objet::applyScale(){
	glScaled(m_scale[0], m_scale[1], m_scale[2]);
}

void Objet::applyMaterials(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambient.a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse.a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular.a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_emission.a);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}
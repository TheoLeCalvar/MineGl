#ifndef OBJET_H
#define OBJET_H 

#include "vect3D.hpp"
#include "vect4D.hpp"
#include "renderer.hpp"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


class Objet
{
protected:
  static Renderer *      _renderer;

protected:
  Vect3D          m_translation;
  Vect3D          m_scale;
  Vect3D          m_rotation_axe;
  GLdouble        m_rotation_angle;
  bool            display_normale;
  Vect4D<GLfloat> m_ambient;
  Vect4D<GLfloat> m_diffuse;
  Vect4D<GLfloat> m_specular;
  Vect4D<GLfloat> m_emission;
  GLfloat         m_shininess;

public:
	Objet();
	virtual ~Objet();

	virtual void display() = 0;
  virtual void switch_normale(){display_normale = !display_normale;}

  static  void setRenderer(Renderer * r){_renderer = r;}

 	virtual void setTranslation(Vect3D v);
  virtual void setTranslation(GLdouble x, GLdouble y, GLdouble z);
  virtual void setScale(Vect3D v);
  virtual void setScale(GLdouble x, GLdouble y, GLdouble z);
  virtual void setRotation(Vect4D<GLdouble> v);
  virtual void setRotation(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);

  virtual void setAmbient(Vect4D<GLfloat> v);
  virtual void setDiffuse(Vect4D<GLfloat> v);
  virtual void setSpecular(Vect4D<GLfloat> v);
  virtual void setEmission(Vect4D<GLfloat> v);
  virtual void setShininess(GLfloat v);


protected:
  virtual void applyRotation();
  virtual void applyTranslation();
  virtual void applyMaterials();
  virtual void applyScale();
	
};


#endif

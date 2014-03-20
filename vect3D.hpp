#ifndef VECT3D_H
#define VECT3D_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


class Vect3D
{
public:
	GLdouble a[3];


	Vect3D(GLdouble x, GLdouble y, GLdouble z);
	Vect3D(Vect3D const & v);
	Vect3D(Vect3D const & p, Vect3D const & p2);
	Vect3D();
	~Vect3D();
	void copy(Vect3D v);

	Vect3D 	operator+(Vect3D v);
	Vect3D & operator+=(Vect3D v);
 	Vect3D 	operator-(Vect3D v);
 	Vect3D & operator-=(Vect3D v);
	Vect3D 	operator-(void);
	Vect3D 	operator*(Vect3D v);
	Vect3D 	operator*(GLdouble t);
	Vect3D 	operator/(GLdouble t);
	//set le vecteur avec les paramètres
	void    operator ()(GLdouble x, GLdouble y, GLdouble z);

	//retourne vrai si le vecteur est nul
	bool 	operator!();
	GLdouble &	operator[](int i);

	GLdouble length();
	void 	normalize();
	GLdouble innerProduct(Vect3D v);
	void 	set(GLdouble x,GLdouble y, GLdouble z);
	Vect3D 	scalarMult(GLdouble a);

	GLdouble * getVector(){return a;}

};


#endif
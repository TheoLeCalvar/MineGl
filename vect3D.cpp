#include <cmath>
#include "vect3D.hpp"


Vect3D::Vect3D(GLdouble x, GLdouble y, GLdouble z) {
	this->a[0] = x;
	this->a[1] = y;
	this->a[2] = z;

}

Vect3D::Vect3D(const Vect3D &v) {
	a[0] = v.a[0];
	a[1] = v.a[1];
	a[2] = v.a[2];
}

Vect3D::Vect3D(const Vect3D &p1, const Vect3D &p2) {
	a[0] = p2.a[0] - p1.a[0];
	a[1] = p2.a[1] - p1.a[1];
	a[2] = p2.a[2] - p1.a[1];
}

Vect3D::Vect3D() {
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
}

Vect3D::~Vect3D(){}


Vect3D Vect3D::operator+(Vect3D v) {

	Vect3D res;

	res.a[0] = a[0] + v.a[0];
	res.a[1] = a[1] + v.a[1];
	res.a[2] = a[2] + v.a[2];

	return(res);
}

Vect3D Vect3D::operator-(Vect3D v) {

	Vect3D res;

	res.a[0] = a[0] - v.a[0];
	res.a[1] = a[1] - v.a[1];
	res.a[2] = a[2] - v.a[2];

	return(res);
}

Vect3D Vect3D::operator-(void) {

	Vect3D res;

	res.a[0] = -a[0];
	res.a[1] = -a[1];
	res.a[2] = -a[2];

	return(res);
}


Vect3D Vect3D::operator*(Vect3D v) {

	Vect3D res;

	res.a[0] = a[1] * v.a[2] - a[2] * v.a[1];
	res.a[1] = a[2] * v.a[0] - a[0] * v.a[2];
	res.a[2] = a[0] * v.a[1] - a[1] * v.a[0];

	return (res);
}

Vect3D Vect3D::operator*(GLdouble t) {

	Vect3D res;

	res.a[0] = a[0] * t;
	res.a[1] = a[1] * t;
	res.a[2] = a[2] * t;

	return (res);
}


Vect3D Vect3D::operator/(GLdouble t) {

	Vect3D res;

	res.a[0] = a[0] / t;
	res.a[1] = a[1] / t;
	res.a[2] = a[2] / t;

	return (res);
}

GLdouble Vect3D::operator[](int i){
	return a[i];
}


GLdouble Vect3D::length() 
{
	return((GLdouble)sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]));
}

void Vect3D::normalize() 
{
	GLdouble len;

	len = length();
	if (len) {
		a[0] /= len;;
		a[1] /= len;
		a[2] /= len;
	}
}


GLdouble Vect3D::innerProduct(Vect3D v) 
{
	return (a[0] * v.a[0] + a[1] * v.a[1] + a[2] * v.a[2]);
}

void Vect3D::copy(Vect3D v) 
{
	a[0] = v.a[0];
	a[1] = v.a[1];
	a[2] = v.a[2];
}

void Vect3D::set(GLdouble x,GLdouble y, GLdouble z) 
{
	this->a[0] = x;
	this->a[1] = y;
	this->a[2] = z;
}

Vect3D Vect3D::scalarMult(GLdouble t) 
{
	Vect3D res;

	res.a[0] = a[0] * t;
	res.a[1] = a[1] * t;
	res.a[2] = a[2] * t;

	return res;
}
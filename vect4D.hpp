#ifndef VECT4D_H
#define VECT4D_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

template <typename T>
class Vect4D
{
public:
	T a[4];


	Vect4D(T x, T y, T z, T w)
	{
		a[0] = x;	
		a[1] = y;
		a[2] = z;
		a[3] = w;
	}

	Vect4D(Vect4D<T> const & v)
	{
		a[0] = v.a[0];
		a[1] = v.a[1];
		a[2] = v.a[2];
		a[3] = v.a[3];
	}

	~Vect4D(){}

	void copy(Vect4D<T> v)
	{
		a[0] = v.a[0];
		a[1] = v.a[1];
		a[2] = v.a[2];
		a[3] = v.a[3];		
	}

	Vect4D<T> 	operator+(Vect4D<T> v)
	{
		Vect4D<T> res;

		res.a[0] = a[0] + v.a[0];
		res.a[1] = a[1] + v.a[1];
		res.a[2] = a[2] + v.a[2];
		res.a[3] = a[3] + v.a[3];

		return(res);		
	}

	Vect4D<T> 	operator-(Vect4D<T> v)
	{
		Vect4D<T> res;

		res.a[0] = a[0] - v.a[0];
		res.a[1] = a[1] - v.a[1];
		res.a[2] = a[2] - v.a[2];
		res.a[3] = a[3] - v.a[3];

		return(res);
	}

	Vect4D<T> 	operator-(void)
	{
		Vect4D<T> res;

		res.a[0] = -a[0];
		res.a[1] = -a[1];
		res.a[2] = -a[2];
		res.a[3] = -a[3];

		return(res);	
	}

	Vect4D<T> 	operator*(T t)
	{
		Vect4D<T> res;

		res.a[0] = a[0] * t;
		res.a[1] = a[1] * t;
		res.a[2] = a[2] * t;
		res.a[3] = a[3] * t;

		return (res);
	}

	Vect4D<T> 	operator/(T t)
	{
		Vect4D<T> res;

		res.a[0] = a[0] / t;
		res.a[1] = a[1] / t;
		res.a[2] = a[2] / t;
		res.a[3] = a[3] / t;

		return (res);	
	}

	T	operator[](int i)
	{
		return a[i];
	}

	GLdouble length()
	{
		return((GLdouble)sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2] + a[3]*a[3]));
	}

	void 	normalize()
	{
		GLdouble len;

		len = length();
		if (len) {
			a[0] /= len;;
			a[1] /= len;
			a[2] /= len;
			a[3] /= len;
		}	
	}

	GLdouble innerProduct(Vect4D v)
	{
		return (a[0] * v.a[0] + a[1] * v.a[1] + a[2] * v.a[2] + a[3] * v.a[3]);
	}

	void 	set(T x,T y, T z, T w)
	{
		a[0] = x;
		a[1] = y;
		a[2] = z;
		a[3] = w;	
	}
	Vect4D 	scalarMult(T a)
	{
		Vect4D res;

		res.a[0] = a[0] * a;
		res.a[1] = a[1] * a;
		res.a[2] = a[2] * a;
		res.a[3] = a[3] * a;

		return res;
	}

	T * getVector(){return a;}

};


#endif
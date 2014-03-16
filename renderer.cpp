#include "renderer.hpp"
#include <string.h> //memcpy
#include <iostream>


Renderer * 	Renderer::_instance = NULL;

Renderer::Renderer(): 
_useNormals(true), _normX(0.0f), _normY(0.0f), _normZ(1.0f),
_useTex(true), _texU(0.0f), _texV(0.0f), 
_transX(0.0f), _transY(0.0f), _transZ(0.0f),
_buffer(NULL), _bufSize(0), _bufIndex(0), _verticesCount(0)
{

}

Renderer::~Renderer()
{
	delete [] _buffer;
}

Renderer * 	Renderer::create()
{
	if (!_instance)
	{
		_instance = new Renderer();
	}

	return _instance;
}

void 		Renderer::destroy()
{
	if (_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}

void 		Renderer::clean()
{
	_verticesCount = 0;
	_bufIndex = 0;

}

void 		Renderer::setBlending(bool b)
{
	if (b)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void 		Renderer::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
	//buffer pas assez grand ou vide
	if (_bufIndex + 8 >= _bufSize)
	{
		if (_bufSize == 0)
		{
			_bufSize = 0x10000;
			_buffer = new GLfloat[_bufSize];
		}
		else
		{
			GLfloat * tmp = new GLfloat[(_bufSize * 2) * sizeof(GLfloat)];
			memcpy(tmp, _buffer, _bufSize * sizeof(GLfloat));
			_bufSize *= 2;
			delete [] _buffer;
			_buffer = tmp;
		}
	}

	_verticesCount++;

	_buffer[_bufIndex] 		= x + _transX;
	_buffer[_bufIndex + 1]	= y + _transY;
	_buffer[_bufIndex + 2] 	= z + _transZ;

	if (_useTex)
	{
		_buffer[_bufIndex + 3] 	= _texU;
		_buffer[_bufIndex + 4] 	= _texV;
	}

	if (_useNormals)
	{
		_buffer[_bufIndex + 5]  = _normX;
		_buffer[_bufIndex + 6]  = _normY;
		_buffer[_bufIndex + 7]  = _normZ;
	}

	_bufIndex += 8;
}


void 		Renderer::addVertex(GLfloat * v)
{
	addVertex(v[0], v[1], v[2]);
}

void 		Renderer::addVertexUV(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v)
{
	_texU = u;
	_texV = v;
	addVertex(x, y, z);
}

void 		Renderer::addVertexUV(GLfloat *w, GLfloat u, GLfloat v)
{
	_texU = u;
	_texV = v;
	addVertex(w[0], w[1], w[2]);
}

void 		Renderer::setNormal(GLfloat x, GLfloat y, GLfloat z)
{
	_normX = x;
	_normY = y;
	_normZ = z;
}

void 		Renderer::setNormal(GLfloat *v)
{
	_normX = v[0];
	_normY = v[1];
	_normZ = v[2];
}

void 		Renderer::setActiveTex(GLuint id)
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void 		Renderer::useNormals(bool b)
{
	_useNormals = b;
}

void 		Renderer::setTranslation(GLfloat x, GLfloat y, GLfloat z)
{
	_transX = x;
	_transY = y;
	_transZ = z;
}


void 		Renderer::setTranslation(GLfloat *v)
{
	setTranslation(v[0], v[1], v[2]);
}

void 		Renderer::display()
{
	static GLfloat amb[] = {0.2f, 0.2f, 0.2f, 1.0f};
	static GLfloat dif[] = {0.8f, 0.8f, 0.8f, 1.0f};
	static GLfloat spe[] = {0.0f, 0.0f, 0.0f, 1.0f};


	glPushMatrix();
		
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
		glMaterialfv(GL_BACK, GL_AMBIENT, spe);
		glMaterialfv(GL_BACK, GL_DIFFUSE, spe);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 0);


		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 8 * sizeof(GLfloat), _buffer);

		if (_useNormals)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 8 * sizeof(GLfloat), _buffer + 5);
		}

		if (_useTex)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(GLfloat), _buffer + 3);
		}



		glDrawArrays(GL_TRIANGLES, 0, _verticesCount);


		glDisableClientState(GL_VERTEX_ARRAY);

		if (_useNormals)
		{
			glDisableClientState(GL_NORMAL_ARRAY);
		}

		if (_useTex)
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		


	glPopMatrix();
}
#include "cube.hpp"




GLfloat Cube::_points[] = 
{	
	0.5f, 	-0.5f, 	0.5f,	//0 - 0
	0.5f, 	-0.5f, 	-0.5f,	//1 - 3
	0.5f, 	0.5f, 	-0.5f,	//2 - 6
	0.5f, 	0.5f, 	0.5f,	//3 - 9
	-0.5f, 	-0.5f, 	0.5f,	//4 - 12
	-0.5f, 	-0.5f, 	-0.5f,	//5 - 15
	-0.5f, 	0.5f, 	-0.5f,	//6 - 18
	-0.5f, 	0.5f, 	0.5f,	//7 - 21
};


Cube::Cube(GLfloat size, char visibility):
_visibility(visibility)
{
	setScale(size, size, size);
}

void Cube::display(){
	_renderer->setTranslation(m_translation[0], m_translation[1], m_translation[2]);

	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(1.0f, 0.0f, 0.0f);
		_renderer->addVertex(_points);
		_renderer->addVertex(_points + 3);
		_renderer->addVertex(_points + 6);

		_renderer->addVertex(_points);
		_renderer->addVertex(_points + 6);
		_renderer->addVertex(_points + 9);
	}

	if (_visibility & RIGHT)
	{
		//face droite
		_renderer->setNormal(0.0f, 1.0f, 0.0f);
		_renderer->addVertex(_points + 9);
		_renderer->addVertex(_points + 6);
		_renderer->addVertex(_points + 18);

		_renderer->addVertex(_points + 9);
		_renderer->addVertex(_points + 18);
		_renderer->addVertex(_points + 21);
	}

	if (_visibility & BACK)
	{
		//face arriere
		_renderer->setNormal(-1.0f, 0.0f, 0.0f);
		_renderer->addVertex(_points + 21);
		_renderer->addVertex(_points + 18);
		_renderer->addVertex(_points + 15);

		_renderer->addVertex(_points + 21);
		_renderer->addVertex(_points + 15);
		_renderer->addVertex(_points + 12);
	}

	if (_visibility & LEFT)
	{
		//face gauche
		_renderer->setNormal(0.0f, -1.0f, 0.0f);
		_renderer->addVertex(_points + 12);
		_renderer->addVertex(_points + 15);
		_renderer->addVertex(_points + 3);

		_renderer->addVertex(_points + 12);
		_renderer->addVertex(_points + 3);
		_renderer->addVertex(_points);
	}

	if (_visibility & TOP)
	{
		//face haute
		_renderer->setNormal(0.0f, 0.0f, 1.0f);
		_renderer->addVertex(_points);
		_renderer->addVertex(_points + 9);
		_renderer->addVertex(_points + 21);

		_renderer->addVertex(_points);
		_renderer->addVertex(_points + 21);
		_renderer->addVertex(_points + 12);
	}

	if (_visibility & BACK)
	{
		//face basse
		_renderer->setNormal(0.0f, 0.0f, -1.0f);
		_renderer->addVertex(_points + 3);
		_renderer->addVertex(_points + 15);
		_renderer->addVertex(_points + 18);

		_renderer->addVertex(_points + 3);
		_renderer->addVertex(_points + 18);
		_renderer->addVertex(_points + 6);
	}

}

void Cube::setVisibility(side s, bool b)
{
	if (b)
	{
		_visibility |= s;
	}
	else
	{
		_visibility &= (!s & 127);
	}
}
#include "grass.hpp"


Grass::Grass(GLfloat size, char visibility):
Cube(size, visibility)
{

}

void Grass::display()
{
	_renderer->setTranslation(m_translation[0], m_translation[1], m_translation[2]);

	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(1.0f, 0.0f, 0.0f);
		_renderer->addVertexUV(_points, 16/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 3, 16/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 6, 31/64.0f, 15/64.0f);

		_renderer->addVertexUV(_points, 16/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 6, 31/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 9, 31/64.0f, 0.0f);
	}

	if (_visibility & RIGHT)
	{
		//face droite
		_renderer->setNormal(0.0f, 1.0f, 0.0f);
		_renderer->addVertexUV(_points + 9, 16/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 6, 16/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 18, 31/64.0f, 15/64.0f);

		_renderer->addVertexUV(_points + 9, 16/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 18, 31/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 21, 31/64.0f, 0.0f);
	}

	if (_visibility & BACK)
	{
		//face arriere
		_renderer->setNormal(-1.0f, 0.0f, 0.0f);
		_renderer->addVertexUV(_points + 21, 16/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 18, 16/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 15, 31/64.0f, 15/64.0f);

		_renderer->addVertexUV(_points + 21, 16/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 15, 31/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 12, 31/64.0f, 0.0f);
	}

	if (_visibility & LEFT)
	{
		//face gauche
		_renderer->setNormal(0.0f, -1.0f, 0.0f);
		_renderer->addVertexUV(_points + 12, 16/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 15, 16/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 3, 31/64.0f, 15/64.0f);

		_renderer->addVertexUV(_points + 12, 16/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 3, 31/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points, 31/64.0f, 0.0f);
	}

	if (_visibility & TOP)
	{
		//face haute
		_renderer->setNormal(0.0f, 0.0f, 1.0f);
		_renderer->addVertexUV(_points, 0.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 9, 15/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 21, 15/64.0f, 0.0f);

		_renderer->addVertexUV(_points, 0.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 21, 15/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 12, 0.0f, 0.0f);
	}

	if (_visibility & BOT)
	{
		//face basse
		_renderer->setNormal(0.0f, 0.0f, -1.0f);
		_renderer->addVertexUV(_points + 3, 32/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 15, 32/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 18, 47/64.0f, 15/64.0f);

		_renderer->addVertexUV(_points + 3, 32/64.0f, 0.0f);
		_renderer->addVertexUV(_points + 18, 47/64.0f, 15/64.0f);
		_renderer->addVertexUV(_points + 6, 47/64.0f, 0.0f);
	}
}
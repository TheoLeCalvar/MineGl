#include "dirt.hpp"


Dirt::Dirt(GLfloat size, char visibility):
Cube(size, visibility)
{

}

void Dirt::display()
{
	_renderer->setTranslation(m_translation[0], m_translation[1], m_translation[2]);

	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(1.0f, 0.0f, 0.0f);
		_renderer->addVertexUV(_points, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 3, DIRT_UMIN, DIRT_VMAX);
		_renderer->addVertexUV(_points + 6, DIRT_UMAX, DIRT_VMAX);

		_renderer->addVertexUV(_points, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 6, DIRT_UMAX, DIRT_VMAX);
		_renderer->addVertexUV(_points + 9, DIRT_UMAX, DIRT_VMIN);
	}

	if (_visibility & RIGHT)
	{
		//face droite
		_renderer->setNormal(0.0f, 1.0f, 0.0f);
		_renderer->addVertexUV(_points + 9, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 6, DIRT_UMIN, DIRT_VMAX);
		_renderer->addVertexUV(_points + 18, DIRT_UMAX, DIRT_VMAX);

		_renderer->addVertexUV(_points + 9, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 18, DIRT_UMAX, DIRT_VMAX);
		_renderer->addVertexUV(_points + 21, DIRT_UMAX, DIRT_VMIN);
	}

	if (_visibility & BACK)
	{
		//face arriere
		_renderer->setNormal(-1.0f, 0.0f, 0.0f);
		_renderer->addVertexUV(_points + 21, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 18, DIRT_UMIN, DIRT_VMAX);
		_renderer->addVertexUV(_points + 15, DIRT_UMAX, DIRT_VMAX);

		_renderer->addVertexUV(_points + 21, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 15, DIRT_UMAX, DIRT_VMAX);
		_renderer->addVertexUV(_points + 12, DIRT_UMAX, DIRT_VMIN);
	}

	if (_visibility & LEFT)
	{
		//face gauche
		_renderer->setNormal(0.0f, -1.0f, 0.0f);
		_renderer->addVertexUV(_points + 12, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 15, DIRT_UMIN, DIRT_VMAX);
		_renderer->addVertexUV(_points + 3, DIRT_UMAX, DIRT_VMAX);

		_renderer->addVertexUV(_points + 12, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 3, DIRT_UMAX, DIRT_VMAX);
		_renderer->addVertexUV(_points, DIRT_UMAX, DIRT_VMIN);
	}

	if (_visibility & TOP)
	{
		//face haute
		_renderer->setNormal(0.0f, 0.0f, 1.0f);
		_renderer->addVertexUV(_points, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 9, DIRT_UMIN, DIRT_VMAX);
		_renderer->addVertexUV(_points + 21, DIRT_UMAX, DIRT_VMAX);

		_renderer->addVertexUV(_points, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 21, DIRT_UMAX, DIRT_VMAX);
		_renderer->addVertexUV(_points + 12, DIRT_UMAX, DIRT_VMIN);
	}

	if (_visibility & BOT)
	{
		//face basse
		_renderer->setNormal(0.0f, 0.0f, -1.0f);
		_renderer->addVertexUV(_points + 3, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 15, DIRT_UMIN, DIRT_VMAX);
		_renderer->addVertexUV(_points + 18, DIRT_UMAX, DIRT_VMAX);

		_renderer->addVertexUV(_points + 3, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 18, DIRT_UMAX, DIRT_VMAX);
		_renderer->addVertexUV(_points + 6, DIRT_UMAX, DIRT_VMIN);
	}
}
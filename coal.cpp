#include "coal.hpp"

Coal::Coal(GLfloat size, char visibility):
Cube(size, visibility)
{

}

void Coal::display()
{
	_renderer->setTranslation(m_translation[0], m_translation[1], m_translation[2]);

	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(1.0f, 0.0f, 0.0f);
		_renderer->addVertexUV(_points, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 3, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 6, COAL_UMAX, COAL_VMAX);

		_renderer->addVertexUV(_points, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 6, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points + 9, COAL_UMAX, COAL_VMIN);
	}

	if (_visibility & RIGHT)
	{
		//face droite
		_renderer->setNormal(0.0f, 1.0f, 0.0f);
		_renderer->addVertexUV(_points + 9, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 6, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 18, COAL_UMAX, COAL_VMAX);

		_renderer->addVertexUV(_points + 9, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 18, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points + 21, COAL_UMAX, COAL_VMIN);
	}

	if (_visibility & BACK)
	{
		//face arriere
		_renderer->setNormal(-1.0f, 0.0f, 0.0f);
		_renderer->addVertexUV(_points + 21, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 18, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 15, COAL_UMAX, COAL_VMAX);

		_renderer->addVertexUV(_points + 21, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 15, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points + 12, COAL_UMAX, COAL_VMIN);
	}

	if (_visibility &  LEFT)
	{
		//face gauche
		_renderer->setNormal(0.0f, -1.0f, 0.0f);
		_renderer->addVertexUV(_points + 12, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 15, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 3, COAL_UMAX, COAL_VMAX);

		_renderer->addVertexUV(_points + 12, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 3, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points, COAL_UMAX, COAL_VMIN);
	}

	if (_visibility & TOP)
	{
		//face haute
		_renderer->setNormal(0.0f, 0.0f, 1.0f);
		_renderer->addVertexUV(_points, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 9, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 21, COAL_UMAX, COAL_VMAX);

		_renderer->addVertexUV(_points, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 21, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points + 12, COAL_UMAX, COAL_VMIN);
	}

	if (_visibility & BOT)
	{
		//face basse
		_renderer->setNormal(0.0f, 0.0f, -1.0f);
		_renderer->addVertexUV(_points + 3, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 15, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 18, COAL_UMAX, COAL_VMAX);

		_renderer->addVertexUV(_points + 3, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 18, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points + 6, COAL_UMAX, COAL_VMIN);
	}
}
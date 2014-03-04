#include "stone.hpp"


Stone::Stone(GLfloat size, char visibility):
Cube(size, visibility)
{

}

void Stone::display()
{
	_renderer->setTranslation(m_translation[0], m_translation[1], m_translation[2]);

	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(1.0f, 0.0f, 0.0f);
		_renderer->addVertexUV(_points, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 3, STONE_UMIN, STONE_VMAX);
		_renderer->addVertexUV(_points + 6, STONE_UMAX, STONE_VMAX);

		_renderer->addVertexUV(_points, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 6, STONE_UMAX, STONE_VMAX);
		_renderer->addVertexUV(_points + 9, STONE_UMAX, STONE_VMIN);
	}

	if (_visibility & RIGHT)
	{
		//face droite
		_renderer->setNormal(0.0f, 1.0f, 0.0f);
		_renderer->addVertexUV(_points + 9, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 6, STONE_UMIN, STONE_VMAX);
		_renderer->addVertexUV(_points + 18, STONE_UMAX, STONE_VMAX);

		_renderer->addVertexUV(_points + 9, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 18, STONE_UMAX, STONE_VMAX);
		_renderer->addVertexUV(_points + 21, STONE_UMAX, STONE_VMIN);
	}

	if (_visibility & BACK)
	{
		//face arriere
		_renderer->setNormal(-1.0f, 0.0f, 0.0f);
		_renderer->addVertexUV(_points + 21, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 18, STONE_UMIN, STONE_VMAX);
		_renderer->addVertexUV(_points + 15, STONE_UMAX, STONE_VMAX);

		_renderer->addVertexUV(_points + 21, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 15, STONE_UMAX, STONE_VMAX);
		_renderer->addVertexUV(_points + 12, STONE_UMAX, STONE_VMIN);
	}

	if (_visibility & LEFT)
	{
		//face gauche
		_renderer->setNormal(0.0f, -1.0f, 0.0f);
		_renderer->addVertexUV(_points + 12, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 15, STONE_UMIN, STONE_VMAX);
		_renderer->addVertexUV(_points + 3, STONE_UMAX, STONE_VMAX);

		_renderer->addVertexUV(_points + 12, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 3, STONE_UMAX, STONE_VMAX);
		_renderer->addVertexUV(_points, STONE_UMAX, STONE_VMIN);
	}

	if (_visibility & TOP)
	{
		//face haute
		_renderer->setNormal(0.0f, 0.0f, 1.0f);
		_renderer->addVertexUV(_points, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 9, STONE_UMIN, STONE_VMAX);
		_renderer->addVertexUV(_points + 21, STONE_UMAX, STONE_VMAX);

		_renderer->addVertexUV(_points, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 21, STONE_UMAX, STONE_VMAX);
		_renderer->addVertexUV(_points + 12, STONE_UMAX, STONE_VMIN);
	}

	if (_visibility & BOT)
	{
		//face basse
		_renderer->setNormal(0.0f, 0.0f, -1.0f);
		_renderer->addVertexUV(_points + 3, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 15, STONE_UMIN, STONE_VMAX);
		_renderer->addVertexUV(_points + 18, STONE_UMAX, STONE_VMAX);

		_renderer->addVertexUV(_points + 3, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 18, STONE_UMAX, STONE_VMAX);
		_renderer->addVertexUV(_points + 6, STONE_UMAX, STONE_VMIN);
	}
}
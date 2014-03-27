#include "stone.hpp"


Stone::Stone(unsigned char visibility):
Cube(visibility)
{

}

void Stone::display()
{

	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(_normals);
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
		_renderer->setNormal(_normals + 3);
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
		_renderer->setNormal(_normals + 6);
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
		_renderer->setNormal(_normals + 9);
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
		_renderer->setNormal(_normals + 12);
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
		_renderer->setNormal(_normals + 15);
		_renderer->addVertexUV(_points + 3, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 15, STONE_UMIN, STONE_VMAX);
		_renderer->addVertexUV(_points + 18, STONE_UMAX, STONE_VMAX);

		_renderer->addVertexUV(_points + 3, STONE_UMIN, STONE_VMIN);
		_renderer->addVertexUV(_points + 18, STONE_UMAX, STONE_VMAX);
		_renderer->addVertexUV(_points + 6, STONE_UMAX, STONE_VMIN);
	}
}

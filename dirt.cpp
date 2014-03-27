#include "dirt.hpp"


Dirt::Dirt(unsigned char visibility):
Cube(visibility)
{

}

void Dirt::display()
{

	if (_visibility & FRONT)
	{
		//face avant

		_renderer->setNormal(_normals);
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
		
		_renderer->setNormal(_normals + 3);
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

		_renderer->setNormal(_normals + 6);
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

		_renderer->setNormal(_normals + 9);
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

		_renderer->setNormal(_normals + 12);
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

		_renderer->setNormal(_normals + 15);
		_renderer->addVertexUV(_points + 3, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 15, DIRT_UMIN, DIRT_VMAX);
		_renderer->addVertexUV(_points + 18, DIRT_UMAX, DIRT_VMAX);

		_renderer->addVertexUV(_points + 3, DIRT_UMIN, DIRT_VMIN);
		_renderer->addVertexUV(_points + 18, DIRT_UMAX, DIRT_VMAX);
		_renderer->addVertexUV(_points + 6, DIRT_UMAX, DIRT_VMIN);
	}
}

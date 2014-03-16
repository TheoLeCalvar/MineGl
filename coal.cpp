#include "coal.hpp"

Coal::Coal(unsigned char visibility):
Cube(visibility)
{

}

void Coal::display()
{
	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(_normals);
		_renderer->addVertexUV(_points, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 3, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 6, COAL_UMAX, COAL_VMAX);

		_renderer->setNormal(_normals);
		_renderer->addVertexUV(_points, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 6, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points + 9, COAL_UMAX, COAL_VMIN);
	}

	if (_visibility & RIGHT)
	{
		//face droite
		_renderer->setNormal(_normals + 3);
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
		_renderer->setNormal(_normals + 6);
		_renderer->addVertexUV(_points + 21, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 18, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 15, COAL_UMAX, COAL_VMAX);

		_renderer->addVertexUV(_points + 21, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 15, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points + 12, COAL_UMAX, COAL_VMIN);
	}

	if (_visibility & LEFT)
	{
		//face gauche
		_renderer->setNormal(_normals + 9);
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
		_renderer->setNormal(_normals + 12);
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
		_renderer->setNormal(_normals + 15);
		_renderer->addVertexUV(_points + 3, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 15, COAL_UMIN, COAL_VMAX);
		_renderer->addVertexUV(_points + 18, COAL_UMAX, COAL_VMAX);

		_renderer->addVertexUV(_points + 3, COAL_UMIN, COAL_VMIN);
		_renderer->addVertexUV(_points + 18, COAL_UMAX, COAL_VMAX);
		_renderer->addVertexUV(_points + 6, COAL_UMAX, COAL_VMIN);
	}
}
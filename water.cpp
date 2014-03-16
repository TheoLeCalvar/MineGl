#include "water.hpp"
#include <GLFW/glfw3.h>

unsigned char Water::_frame = 0;

Water::Water(unsigned char visibility):
Cube(visibility)
{

}

void Water::inc()
{
	static double time = glfwGetTime();

	if (glfwGetTime() - time > 1.0f/30.0f)
	{
		_frame = (_frame + 1) % 64;
		time = glfwGetTime();
	}
}


void Water::display()
{
	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(_normals);
		_renderer->addVertexUV(_points, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 3, 1.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 6, 1.0f, (15 + 16*_frame) / 1024.0f);

		_renderer->addVertexUV(_points, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 6, 1.0f, (15 + 16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 9, 0.0f, (15 + 16*_frame) / 1024.0f);
	}

	if (_visibility & RIGHT)
	{
		//face droite
		_renderer->setNormal(_normals + 9);
		_renderer->addVertexUV(_points + 9, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 6, 1.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 18, 1.0f, (15 + 16*_frame) / 1024.0f);

		_renderer->addVertexUV(_points + 9, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 18, 1.0f, (15 + 16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 21, 0.0f, (15 + 16*_frame) / 1024.0f);
	}

	if (_visibility & BACK)
	{
		//face arriere
		_renderer->setNormal(_normals + 21);
		_renderer->addVertexUV(_points + 21, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 18, 1.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 15, 1.0f, (15 + 16*_frame) / 1024.0f);

		_renderer->addVertexUV(_points + 21, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 15, 1.0f, (15 + 16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 12, 0.0f, (15 + 16*_frame) / 1024.0f);
	}

	if (_visibility & LEFT)
	{
		//face gauche
		_renderer->setNormal(_normals + 12);
		_renderer->addVertexUV(_points + 12, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 15, 1.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 3, 1.0f, (15 + 16*_frame) / 1024.0f);

		_renderer->addVertexUV(_points + 12, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 3, 1.0f, (15 + 16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points, 0.0f, (15 + 16*_frame) / 1024.0f);
	}

	if (_visibility & TOP)
	{
		//face haute
		_renderer->setNormal(_normals);
		_renderer->addVertexUV(_points, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 9, 1.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 21, 1.0f, (15 + 16*_frame) / 1024.0f);

		_renderer->addVertexUV(_points, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 21, 1.0f, (15 + 16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 12, 0.0f, (15 + 16*_frame) / 1024.0f);
	}

	if (_visibility & BOT)
	{
		//face basse
		_renderer->setNormal(_normals + 3);
		_renderer->addVertexUV(_points + 3, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 15, 1.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 18, 1.0f, (15 + 16*_frame) / 1024.0f);

		_renderer->addVertexUV(_points + 3, 0.0f, (16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 18, 1.0f, (15 + 16*_frame) / 1024.0f);
		_renderer->addVertexUV(_points + 6, 0.0f, (15 + 16*_frame) / 1024.0f);
	}
}
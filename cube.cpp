#include "cube.hpp"


Renderer * Cube::_renderer = NULL;
GLuint Cube::_texId[] = {0, 0};


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

// GLfloat Cube::_normals[] =
// {
// 	0.57735f, -0.57735f, 0.57735f,
// 	0.57735f, -0.57735f, -0.57735f,
// 	0.57735f, 0.57735f, -0.57735f, 
// 	0.57735f, 0.57735f, 0.57735f
// 	-0.57735f, -0.57735f, 0.57735f,
// 	-0.57735f, -0.57735f, -0.57735f,
// 	-0.57735f, 0.57735f, -0.57735f,
// 	-0.57735f, 0.57735f, 0.57735f
// };

GLfloat Cube::_normals[] =
{
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 
	0.0f, 0.0f, -1.0f 
};

Cube::Cube(unsigned char visibility):
_visibility(visibility)
{
}

void Cube::loadTexture()
{
	int width, height;
	unsigned char  * image;

	glActiveTexture(GL_TEXTURE0);
	image = SOIL_load_image("texture/textures.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glGenTextures(2, _texId);
	glBindTexture(GL_TEXTURE_2D, _texId[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	SOIL_free_image_data(image);


	image = SOIL_load_image("texture/water_still.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, _texId[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	SOIL_free_image_data(image);
}

void Cube::display()
{
	if (_visibility & FRONT)
	{
		//face avant
		_renderer->setNormal(_normals);
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
		_renderer->setNormal(_normals + 3);
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
		_renderer->setNormal(_normals + 6);
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
		_renderer->setNormal(_normals + 9);
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
		_renderer->setNormal(_normals + 12);
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
		_renderer->setNormal(_normals + 15);
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

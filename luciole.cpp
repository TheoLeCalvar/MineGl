#include "luciole.hpp"
#include <cstdlib> //rand
#include <cmath>
#include <iostream>

//vertex 
//normals
GLfloat Luciole::_body[] =
{
	LUCIOLE_LENGHT, 0.0f, 			LUCIOLE_HEIGHT,
	LUCIOLE_LENGHT, 0.0f, 			0.0f,
	LUCIOLE_LENGHT,	LUCIOLE_WIDTH, 	0.0f,
	LUCIOLE_LENGHT, LUCIOLE_WIDTH, 	LUCIOLE_HEIGHT,
	0.0f, 			0.0f,			LUCIOLE_HEIGHT,
	0.0f, 			0.0f,			0.0f,
	0.0f, 			LUCIOLE_WIDTH,	0.0f,
	0.0f, 			LUCIOLE_WIDTH,	LUCIOLE_HEIGHT,
	SQRT3, 			-SQRT3, 		SQRT3,
	SQRT3, 			-SQRT3, 		-SQRT3,
	SQRT3, 			SQRT3, 			-SQRT3,
	SQRT3, 			SQRT3, 			SQRT3,
	-SQRT3, 		-SQRT3, 		SQRT3,
	-SQRT3, 		-SQRT3, 		-SQRT3,
	-SQRT3, 		SQRT3, 			-SQRT3,
	-SQRT3, 		SQRT3, 			SQRT3
};

GLubyte Luciole::_bodyIndices[] =
{
	0, 1, 2, 	0, 2, 3,
	3, 2, 6, 	3, 6, 7,
	7, 6, 5, 	7, 5, 4,
	4, 5, 1, 	4, 1, 0,
	7, 4, 0, 	7, 0, 3,
	6, 2, 1, 	6, 1, 5  
};

GLfloat Luciole::_wing[] =
{
	0.0f, 				0.0f, 				0.0f,
	LUCIOLE_LENGHT/2, 	-LUCIOLE_WIDTH*2, 	0.0f,
	0.0f, 				-LUCIOLE_WIDTH*3,	0.0f,
	-LUCIOLE_LENGHT/2, 	-LUCIOLE_WIDTH*2,	0.0f,
	0.0f, 				-LUCIOLE_WIDTH*2, 	0.0f
};

GLubyte Luciole::_wingIndices[] =
{
	//front
	4, 1, 0,
	4, 2, 1,
	4, 3, 2,
	4, 0, 3,
	//back
	4, 3, 0,
	4, 2, 3,
	4, 1, 2,
	4, 0, 1
};

GLfloat Luciole::_light[] =
{
	LUCIOLE_LENGHT / 4, 0.0f, 				LUCIOLE_HEIGHT/2,
	LUCIOLE_LENGHT / 4, 0.0f, 				0.0f,
	LUCIOLE_LENGHT / 4,	LUCIOLE_WIDTH/2, 	0.0f,
	LUCIOLE_LENGHT / 4, LUCIOLE_WIDTH/2, 	LUCIOLE_HEIGHT/2,
	0.0f, 				0.0f,				LUCIOLE_HEIGHT/2,
	0.0f, 				0.0f,				0.0f,
	0.0f, 				LUCIOLE_WIDTH/2,	0.0f,
	0.0f, 				LUCIOLE_WIDTH/2,	LUCIOLE_HEIGHT/2,
	SQRT3, 				-SQRT3, 			SQRT3,
	SQRT3, 				-SQRT3, 			-SQRT3,
	SQRT3, 				SQRT3, 				-SQRT3,
	SQRT3, 				SQRT3, 				SQRT3,
	-SQRT3, 			-SQRT3, 			SQRT3,
	-SQRT3, 			-SQRT3, 			-SQRT3,
	-SQRT3, 			SQRT3, 				-SQRT3,
	-SQRT3, 			SQRT3, 				SQRT3
};

GLubyte Luciole::_lightIndices[] =
{
	0, 1, 2, 	0, 2, 3,
	3, 2, 6, 	3, 6, 7,
	7, 6, 5, 	7, 5, 4,
	4, 5, 1, 	4, 1, 0,
	7, 4, 0, 	7, 0, 3,
	6, 2, 1, 	6, 1, 5  
};


Luciole::Luciole(World * w, const Vect3D &pos, GLfloat theta, GLfloat phi):
	_world(w), _pos(pos), _theta(theta), _phi(phi), _alpha(45.0f)
{
	spawn();
}

Luciole::Luciole(World * w):
	_world(w), _theta(0.0f), _phi(0.0f), _alpha(45.0f), _frame(0)
{
	spawn();
}


Luciole::~Luciole()
{
	spawn();
}

void Luciole::spawn()
{
	//on cherche un bloc d'eau
	for (unsigned int i = 0, x = 0, y = 0, z = WATER_LEVEL; x*y < WORLDSIZEX * WORLDSIZEY; ++i)
	{

		if (_world->getCubeType(x, y, z) == Cube::WATER)
		{
			int xL = 0, yL = 0, zL = 0;

			while(true)
			{
				xL = (rand() % 9) - 5;
				yL = (rand() % 9) - 5;
				zL = (rand() % 3) + 1;

				if (_world->empty(x + xL, y + yL, z + zL))
				{
					_pos(static_cast<GLdouble>(x + xL), static_cast<GLdouble>(y + yL), static_cast<GLdouble>(z + zL));
					std::cout << _pos[0] << " " << _pos[1] << " " << _pos[2] << std::endl;
					return;
				}
			}
		}

		++x;
		if (x==WORLDSIZEX)
		{
			++y;
			x = 0;
		}
		if (y == WORLDSIZEY)
		{
			++z;
			y = 0;
		}
	}
}


void Luciole::draw()
{
	//matériaux de l'abdomen
	static GLfloat 		ambient_body[] = {0.0f, 0.0f, 0.0f, 1.0f};
	static GLfloat 		diffuse_body[] = {0.01f, 0.01f, 0.01f, 1.0f};
	static GLfloat		specular_body[] = {0.5f, 0.5f, 0.5f, 1.0f};
	static GLfloat 		emission_body[] = {0.0f, 0.0f, 0.0f, 1.0f};
	static GLfloat 		shininess_body = 32.0f;

	//matériaux des ailes
	static GLfloat 		ambient_wing[] = {223/255.0f, 253/255.0f, 255/255.0f, 0.2f};
	static GLfloat 		diffuse_wing[] = {223/255.0f, 253/255.0f, 255/255.0f, 0.2f};
	static GLfloat		specular_wing[] = {223/255.0f, 253/255.0f, 255/255.0f, 0.2f};
	static GLfloat 		emission_wing[] =  {0.0f, 0.0f, 0.0f, 1.0f};
	static GLfloat 		shininess_wing = 0.0f;

	//matériaux de la zone lumineuse
	static GLfloat 		ambient_light[] = {171/255.0f, 255/255.0f, 46/255.0f, 1.0f};
	static GLfloat 		diffuse_light[] = {171/255.0f, 255/255.0f, 46/255.0f, 1.0f};
	static GLfloat		specular_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
	static GLfloat 		emission_light[] =  {171/255.0f, 255/255.0f, 46/255.0f, 1.0f};
	static GLfloat 		shininess_light = 0.0f;

	static GLfloat 		lumPos[] = {LUCIOLE_LENGHT/8, LUCIOLE_WIDTH / 4, LUCIOLE_HEIGHT / 4, 1.0f};
	static GLfloat 		lumAmb[] = {0.0f, 0.0f, 0.0f, 0.0f};
	static GLfloat 		lumDif[] = {171/255.0f, 255/255.0f, 46/255.0f, 1.0f};
	static GLfloat 		lumSpe[] = {0.0f, 0.0f, 0.0f, 0.0f};


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	//abdomen
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_body);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_body);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_body);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_body);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess_body);


	glPushMatrix();
		//corps
		glTranslatef(_pos[0], _pos[1], _pos[2]);

		glRotatef(_theta, 0.0f, 0.0f, 1.0f);
		glRotatef(_phi, 0.0f, -1.0f, 0.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _body);

		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, _body+24);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, _bodyIndices);

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		//bout fluorescent
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_light);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_light);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_light);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_light);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess_light);


			glTranslatef(LUCIOLE_LENGHT, LUCIOLE_WIDTH / 4, LUCIOLE_HEIGHT / 4);

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, _light);

			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 0, _light+24);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, _lightIndices);

			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);


			glLightfv(GL_LIGHT2, GL_POSITION, lumPos);
			glLightfv(GL_LIGHT2, GL_AMBIENT , lumAmb);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, lumDif);
			glLightfv(GL_LIGHT2, GL_SPECULAR, lumSpe);
			glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.7f);

			glEnable(GL_LIGHT2);


		glPopMatrix();

		//ailes
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_wing);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_wing);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_wing);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission_wing);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess_wing);

			glEnable(GL_BLEND);

			glTranslatef(LUCIOLE_LENGHT / 2, LUCIOLE_WIDTH/2, LUCIOLE_HEIGHT/2);

			glPushMatrix();

				glRotatef(_alpha - 90.0f, 1.0f, 0.0f, 0.0f);

				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(3, GL_FLOAT, 0, _wing);

				glNormal3f(0.0f, 0.0f, 1.0f);
				glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, _wingIndices);

				glNormal3f(0.0f, 0.0f, -1.0f);
				glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, _wingIndices + 12);

			glPopMatrix();
			glPushMatrix();
				glRotatef(-_alpha - 90.0f, 1.0f, 0.0f, 0.0f);

				glNormal3f(0.0f, 0.0f, 1.0f);
				glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, _wingIndices);

				glNormal3f(0.0f, 0.0f, -1.0f);
				glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, _wingIndices + 12);

				glDisableClientState(GL_VERTEX_ARRAY);

				glDisable(GL_BLEND);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();


	AI();


	if (_frame < 30)
	{
		_alpha += 3.0f;
	}
	else
	{
		_alpha -= 3.0f;
	}

	_frame = (_frame + 1) % 60;
}

void Luciole::AI()
{
	static GLfloat thetaCible = _theta;
	static GLfloat thetaOrig = _theta;
	static GLfloat phiCible = _phi;
	static GLfloat phiOrig = _phi;

	if (fabs(_theta - thetaCible) < 0.1f)
	{
		thetaCible = static_cast<GLfloat>(rand() % 360);
		thetaOrig = _theta;
	}

	if (fabs(_phi - phiCible) < 0.1f)
	{
		phiCible = static_cast<GLfloat>((rand() % 180) - 90);
		phiOrig = _phi;
	}


	// std::cout << "phi avant : " << _phi;

	_phi = _phi + (phiCible - phiOrig)/64.f;
	_theta =  _theta + (thetaCible - thetaOrig)/64.0f;

	// std::cout << " | phi : " << _phi << " | phi cible : " << phiCible << " | phiOrig : " << phiOrig << " | diff = " << (phiCible - phiOrig)/64.f << std::endl;
	// std::cout << "theta : " << _theta << " | theta cible : " << thetaCible << std::endl;

	double tmp = cos(_phi * M_PI/180);
	Vect3D avant(tmp * cos(_theta * M_PI/180), tmp * sin(_theta * M_PI/180), sin(_phi * M_PI/180));

	avant.normalize();

	if (_world->empty(_pos + avant * 0.05f))
	{
		_pos -= avant*0.05f;
	}
	else
	{
		_pos -= avant*0.05f;
		_pos[3] = static_cast<GLdouble>(_world->hauteur(static_cast<unsigned int>(_pos[0]), static_cast<unsigned int>(_pos[1])));
	}
}
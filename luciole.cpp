#include "luciole.hpp"
#include <cstdlib> //rand
#include <cmath>
#include <iostream>

int Luciole::_NbLucioles = 0;
Modele * Luciole::_light = NULL;

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

// GLfloat Luciole::_light[] =
// {
// 	LUCIOLE_LENGHT / 4, 0.0f, 				LUCIOLE_HEIGHT/2,
// 	LUCIOLE_LENGHT / 4, 0.0f, 				0.0f,
// 	LUCIOLE_LENGHT / 4,	LUCIOLE_WIDTH/2, 	0.0f,
// 	LUCIOLE_LENGHT / 4, LUCIOLE_WIDTH/2, 	LUCIOLE_HEIGHT/2,
// 	0.0f, 				0.0f,				LUCIOLE_HEIGHT/2,
// 	0.0f, 				0.0f,				0.0f,
// 	0.0f, 				LUCIOLE_WIDTH/2,	0.0f,
// 	0.0f, 				LUCIOLE_WIDTH/2,	LUCIOLE_HEIGHT/2,
// 	SQRT3, 				-SQRT3, 			SQRT3,
// 	SQRT3, 				-SQRT3, 			-SQRT3,
// 	SQRT3, 				SQRT3, 				-SQRT3,
// 	SQRT3, 				SQRT3, 				SQRT3,
// 	-SQRT3, 			-SQRT3, 			SQRT3,
// 	-SQRT3, 			-SQRT3, 			-SQRT3,
// 	-SQRT3, 			SQRT3, 				-SQRT3,
// 	-SQRT3, 			SQRT3, 				SQRT3
// };

// GLubyte Luciole::_lightIndices[] =
// {
// 	0, 1, 2, 	0, 2, 3,
// 	3, 2, 6, 	3, 6, 7,
// 	7, 6, 5, 	7, 5, 4,
// 	4, 5, 1, 	4, 1, 0,
// 	7, 4, 0, 	7, 0, 3,
// 	6, 2, 1, 	6, 1, 5  
// };


Luciole::Luciole(World * w, const Vect3D &pos, GLfloat theta, GLfloat phi):
	_world(w), _pos(pos), _theta(theta), _phi(phi), _thetaCible(theta), _thetaOrig(theta), _thetaFrame(0), _phiCible(_phi), _phiOrig(_phi), _phiFrame(0), _alpha(45.0f)
{
	if (!_light)
	{
		_light = new Modele("modele/sphere.obj");
		_light->useTex(false);
	}

	_id = ++_NbLucioles;
	spawn();
}

Luciole::Luciole(World * w):
	_world(w), _theta(0.0f), _phi(0.0f), _alpha(45.0f), _frame(0)
{
	if (!_light)
	{
		_light = new Modele("modele/sphere.obj");
		_light->useTex(false);
	}

	spawn();
}


Luciole::~Luciole()
{
	_NbLucioles--;
}

void Luciole::spawn()
{
	//on cherche un bloc d'eau
	int x = WORLDSIZEX/ 2, y = WORLDSIZEY / 2, z = 0;
	int xL, yL, zL;

	z = _world->hauteur(x, y);

	while(true)
	{
		xL = (rand() % 9) - 5;
		yL = (rand() % 9) - 5;
		zL = (rand() % 3) + 2;

		if (_world->empty(x + xL, y + yL, z + zL))
		{
			_pos(static_cast<GLdouble>(x + xL), static_cast<GLdouble>(y + yL), static_cast<GLdouble>(z + zL));
			return;
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
			
			glTranslatef(0.0f, LUCIOLE_WIDTH/2.0f, LUCIOLE_HEIGHT);
			glRotatef(90, 0.0f, 0.0f, 1.0f);
			glScalef(0.1f, 0.1f, 0.1f);

			_light->draw();

			glLightfv(GL_LIGHT2 + _id, GL_POSITION, lumPos);
			glLightfv(GL_LIGHT2 + _id, GL_AMBIENT , lumAmb);
			glLightfv(GL_LIGHT2 + _id, GL_DIFFUSE, lumDif);
			glLightfv(GL_LIGHT2 + _id, GL_SPECULAR, lumSpe);
			glLightf(GL_LIGHT2 + _id, GL_LINEAR_ATTENUATION, 0.7f);

			glEnable(GL_LIGHT2 + _id);




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


	// AI();


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

	if (fabs(_theta - _thetaCible) < 0.1f)
	{
		_thetaCible = static_cast<GLdouble>(rand() % 360);
		_thetaOrig = _theta;
		_thetaFrame = 32 + rand() % 100;
	}

	if (fabs(_phi - _phiCible) < 0.1f)
	{
		_phiCible = static_cast<GLdouble>((rand() % 180) - 90);
		_phiOrig = _phi;
		_phiFrame = 32 + rand() % 100;
	}


	_phi += (_phiCible - _phiOrig)/_phiFrame;
	_theta += (_thetaCible - _thetaOrig)/_thetaFrame;


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
		_pos[2] = _world->hauteur(static_cast<unsigned int>(_pos[0]), static_cast<unsigned int>(_pos[1])) + 1.2f;

		_phiCible = -1 * static_cast<GLdouble>(rand() % 90);
		_phiFrame = 32 + rand() % 100;
		_phiOrig = _phi;	
	}
}

Vect3D Luciole::getPos()
{
	return _pos;
}

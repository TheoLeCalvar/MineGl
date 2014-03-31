#include "world.hpp"
#include "player.hpp"
#include "luciole.hpp"

#include <cstdlib> //rand
#include <cmath>
#include <iostream>





World::World(Renderer * renderer):
_renderer(renderer), _listId(0)
{
	Cube::setRenderer(_renderer);
	Cube::loadTexture();


	
	_blocs.reserve(WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ);
	_height.reserve(WORLDSIZEX * WORLDSIZEY);


	genHeight();


	//calcule les visibilités des blocs
	calcVisibility();


	_player = new Player(this);
	
	for (int i = 0; i < 3; ++i)
	{
		_lucioles[i] = new Luciole(this);
	}

}

World::~World()
{
	for (std::vector<Cube *>::iterator i = _blocs.begin(); i != _blocs.end(); ++i)
	{
		if (*i)
		{
			delete *i;
		}
	}
	delete _player;
}

void World::touche(int key, int action)
{
	switch (key)
	{
		case GLFW_KEY_T:
			_player->go(_lucioles[0]->getPos());
		break;

		case GLFW_KEY_4:
		{
			if (action == (GLFW_PRESS))
			{
				static bool b = false;
				for(int i = 0; i < 3; ++i)
					_lucioles[i]->light(b);

				_player->light(b);

				b = !b;
			}

		}


		default:
			_player->toucheJoueur(key, action);
	}

}

void World::sun()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//soleil
	glPushMatrix();
		GLfloat alpha = fmod(glfwGetTime()*2, 360);
		glRotatef(20, 0.0f, 0.0f, 1.0f);
		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glTranslatef(_player->getPositionX(), _player->getPositionY() + 200.0f, _player->getPositionZ());

		glBindTexture(GL_TEXTURE_2D, Cube::_texId[0]);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 32.0f/64.0f);
			glVertex3f(-10.0f, 0.0f, 10.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-10.0f, 0.0f, -10.0f);
			glTexCoord2f(31.0f/64.0f,1.0f);
			glVertex3f(10.0f, 0.0f, -10.0f);
			glTexCoord2f(31.0f/64.0f,32.0f/64.0f);
			glVertex3f(10.0f, 0.0f, 10.0f);
		glEnd();


		GLfloat lum_amb[] = {0.8f, 0.8f, 0.8f, 1.0f};
		GLfloat lum_pos[] = {0.0f, 0.0f, 1.0f, 0.0f};
		GLfloat lum_dif[] = {0.6f, 0.6f, 0.6f, 1.0f};

		glLightfv(GL_LIGHT1, GL_POSITION, lum_pos);
		glLightfv(GL_LIGHT1, GL_AMBIENT , lum_amb);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lum_dif);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lum_amb);

		glEnable(GL_LIGHT1);
	glPopMatrix();
}


void World::draw()
{	
	_player->display();

	sun();


	static std::vector<int> v;

	//affiche les blocs du monde
	if (_listId)
	{
		glCallList(_listId);
	}
	else
	{
		_listId = glGenLists(1);
		GLfloat fog[] = {163/255.0f, 226/255.0f, 255/255.0f, 1.0f};

		glNewList(_listId, GL_COMPILE_AND_EXECUTE);

			glFogf(GL_FOG_MODE, GL_EXP);
			glFogf(GL_FOG_DENSITY, 0.001f);
			glFogf(GL_FOG_START, 100.0f);
			glFogf(GL_FOG_END, 200.0f);
			glFogfv(GL_FOG_COLOR, fog);

			//parcour du monde, affichage des blocs non transparents, stockage des blocs transparent dans un vector temporaire pour un affichage plus tard

			v.clear();
			_renderer->clean();
			_renderer->setActiveTex(Cube::_texId[0]);
			_renderer->setBlending(false);
			_renderer->useMaterial(false);

			for (int i = 0, x = 0, y = 0, z = 0; i < WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ; ++i)
			{
				if (_blocs[i])
				{
					if (_blocs[i]->isTransparent())
					{
						v.push_back(i);
					}
					else
					{	
						_renderer->setTranslation(x, y, z);
						_blocs[i]->display();
					}
				}

				++x;
				if (x == WORLDSIZEX)
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


			_renderer->display();
			
		glEndList();
		_renderer->clean();
	}

	static GLfloat ambient[] = {0.1f, 0.15f, 0.35f, 1.0f};
	static GLfloat diffuse[] = {0.65f, 0.75f, 1.0f, 1.0f};
	static GLfloat specular[] = {0.50f, 0.50f, 0.80f, 1.0f};
	static GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	static GLfloat shininess = 20.0f;


	//affichage des blocs transparents trouvés lors du premier parcours du monde
	_renderer->clean();
	_renderer->setActiveTex(Cube::_texId[1]);
	_renderer->setBlending(true);
	_renderer->useMaterial(true);

	_renderer->setAmbient(ambient);
	_renderer->setDiffuse(diffuse);
	_renderer->setSpecular(specular);
	_renderer->setEmission(emission);
	_renderer->setShininess(shininess);


	for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		_renderer->setTranslation((*i)%WORLDSIZEX,((*i)/WORLDSIZEX)%WORLDSIZEY,  (*i)/(WORLDSIZEX*WORLDSIZEY));
		_blocs[*i]->display();
	}

	_renderer->display();

	for (int i = 0; i < 3; ++i)
	{
		_lucioles[i]->draw();
		_lucioles[i]->AI();
	}

	_player->draw();
	

	Water::inc();
}

void World::genHeight()
{
	float lissage = 0.35f;
	float map[WORLDSIZEX * WORLDSIZEY];
	int espace = WORLDSIZEX;
	Cube * c;




	for (int i = 0; i < WORLDSIZEX * WORLDSIZEY; ++i)
	{
		map[i] = 0.0f;
	}


	map[0]							= WORLDSIZEZ / 2;
	map[WORLDSIZEX-1]				= WORLDSIZEZ / 2;
	map[WORLDSIZEX*(WORLDSIZEY-1)] 	= WORLDSIZEZ / 2;
	map[(WORLDSIZEX*WORLDSIZEY)-1] 	= WORLDSIZEZ / 2;


	//génération de la hauteur du monde, algorithme squareDiamond, inspiré de http://hiko-seijuro.developpez.com/articles/diamond-square/
	while (espace > 1)
	{
		int demiEspace = espace /2;

		//diamand
		for (int x = demiEspace; x < WORLDSIZEX; x += espace)
		{
			for (int y = demiEspace; y < WORLDSIZEY; y += espace)
			{
				int n = 0;
				float somme = 0.0;

				
				if((x-demiEspace >= 0) && (y-demiEspace >= 0))
				{
					somme += map[XY(x-demiEspace, y-demiEspace)];
					n++;
				}

				if ((x-demiEspace >= 0) && (y+demiEspace < WORLDSIZEY))
				{
					somme += map[XY(x-demiEspace, y+demiEspace)];
					n++;
				}
				
				if ((x+demiEspace < WORLDSIZEX) && (y+demiEspace < WORLDSIZEY))
				{
					somme += map[XY(x+demiEspace, y+demiEspace)];
					n++;
				}
				
				if ((x+demiEspace < WORLDSIZEX) && (y-demiEspace >= 0))
				{
					somme += map[XY(x+demiEspace, y-demiEspace)];
					n++;
				}

				map[XY(x,y)] = somme/n + (((double)rand()/RAND_MAX)*2 - 1) * demiEspace * lissage;
			}
		}

		//carre
		for (int x = 0; x < WORLDSIZEX; x += demiEspace)
		{
			int yDebut = ((x/demiEspace) % 2 == 0) ?  demiEspace : 0;

			for (int y = yDebut; y < WORLDSIZEY; y += espace)
			{
				
				// a = (x-espace, y)
				// b = (x, y+espace)
				// c = (x+espace, y)
				// d = (x, y-espace)

				int n = 0;
				float somme = 0.0;

				
				if(x-demiEspace >= 0)
				{
					somme += map[XY(x-demiEspace, y)];
					n++;
				}

				if (y+demiEspace < WORLDSIZEY)
				{
					somme += map[XY(x, y+demiEspace)];
					n++;
				}
				
				if (x+demiEspace < WORLDSIZEX)
				{
					somme += map[XY(x+demiEspace, y)];
					n++;
				}
				
				if (y-demiEspace >= 0)
				{
					somme += map[XY(x, y-demiEspace)];
					n++;
				}

				map[XY(x,y)] = somme/n + (((double)rand()/RAND_MAX)*2 - 1) * demiEspace * lissage;
			}
		}

		espace = demiEspace;
	}


	for (int i = 0; i < WORLDSIZEX * WORLDSIZEY; ++i)
	{
		map[i] = round(map[i]);

		if (map[i] > WORLDSIZEZ)
		{
			map[i] = WORLDSIZEZ;
		}
		else if (map[i] < 0)
		{
			map[i] = 0;
		}
		_height.push_back(map[i]);
	}


	_blocs.reserve(WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ);
	//remplissage du monde en utilisant la map calculée précédément, les blocs de [0, map[x, y]-2] = (Stone 75%, Coal 25%), [map-1, map] = (Dirt, Grass si le bloc du dessus est vide)	
	for (int i = 0, x = 0, y = 0, z = 0; i < WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ; ++i)
	{
		if ((z == map[XY(x, y)]-1) || (z == map[XY(x,y)]))
		{
			c = new Dirt(63);
		}
		else if (z < map[XY(x, y)])
		{
			if (rand()%4)
			{
				c = new Coal(63);
			}
			else
			{
				c = new Stone(63);
			}
		}
		else
		{
			c = NULL;
		}

		_blocs.push_back(c);

		++x;
		if (x == WORLDSIZEX)
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

	//remplacement des blocs d'air par de l'eau pour les blocs en dessous de WATER_LEVEL, voir water.hpp pour la valeur
	for (int i = 0, x = 0, y = 0, z = 0; z <= WATER_LEVEL; ++i)
	{
		if (!_blocs[i])
		{
			_blocs[i] = new Water(127);
		}

		++x;
		if (x == WORLDSIZEX)
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

void World::calcVisibility()
{
	unsigned int x, y, z;
	std::vector<Cube *>::iterator i;

	for (x = 0, y = 0, z = 0, i = _blocs.begin(); i != _blocs.end(); ++i)
	{
		if (*i)
		{			
			//une face est visible si elle n'est pas limite du monde, si le bloc au dessus/dessous/côté est un bloc d'air (NULL) ou transparent dans ce cas le bloc ne doit pas être transparent lui même
			(*i)->setVisibility(
					((x > 0) && (!_blocs[XYZ(x-1, y, z)] || (_blocs[XYZ(x-1, y, z)]->isTransparent() && !(*i)->isTransparent()))? BACK : 0)
				|
					((y > 0) && (!_blocs[XYZ(x, y-1, z)] || (_blocs[XYZ(x, y-1, z)]->isTransparent() && !(*i)->isTransparent()))? LEFT : 0)
				| 
					((z > 0) && (!_blocs[XYZ(x, y, z-1)] || (_blocs[XYZ(x, y, z-1)]->isTransparent() && !(*i)->isTransparent())) ? BOT : 0)
				|
					((x < WORLDSIZEX-1) && (!_blocs[XYZ(x+1, y, z)] || (_blocs[XYZ(x+1, y, z)]->isTransparent() && !(*i)->isTransparent())) ? FRONT : 0)
				| 
					((y < WORLDSIZEY-1) && (!_blocs[XYZ(x, y+1, z)] || (_blocs[XYZ(x, y+1, z)]->isTransparent() && !(*i)->isTransparent())) ? RIGHT : 0)
				| 
					((z < WORLDSIZEZ-1) && (!_blocs[XYZ(x, y, z+1)] || (_blocs[XYZ(x, y, z+1)]->isTransparent() && !(*i)->isTransparent())) ? TOP : 0)
				|
					((*i)->isTransparent() ? TRANSPARENT : 0)
				);
			if (((z < WORLDSIZEZ-1) && !_blocs[XYZ(x, y, z+1)]) && dynamic_cast<Dirt *>((*i)))
			{
				unsigned char vis = (*i)->getVisibility();
				delete *i;
				*i = new Grass(vis);
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

unsigned int World::hauteur(unsigned int x, unsigned int y)
{
	if ((x >= WORLDSIZEX) || (y >= WORLDSIZEY))
	{
		return WATER_LEVEL;
	}
	return (_height[XY(x, y)] < WATER_LEVEL) ? WATER_LEVEL : _height[XY(x, y)];
}

bool 	World::empty(float x, float y, float z)
{
	return (x >= 0) && (x < WORLDSIZEX) && (y >= 0) && (y < WORLDSIZEY) && (z >= 0) && (z < WORLDSIZEZ) && !_blocs[XYZ(static_cast<unsigned int>(x), static_cast<unsigned int>(y), static_cast<unsigned int>(z))];
}

bool 	World::empty(Vect3D p)
{
	return empty(p[0], p[1], p[2]);
}

Cube::cube_type World::getCubeType(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x < WORLDSIZEX) && (y < WORLDSIZEY) && (z < WORLDSIZEZ) && _blocs[XYZ(x, y, z)]) ? _blocs[XYZ(x, y, z)]->getType() : Cube::AIR;
}

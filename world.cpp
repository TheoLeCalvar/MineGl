#include "world.hpp"
#include "player.hpp"

#include <cstdlib> //rand
#include <cmath>
#include <iostream>





World::World(Renderer * renderer):
_renderer(renderer), _listId(0)
{
	Cube::setRenderer(_renderer);
	Cube::loadTexture();
	_player = new Player();

	
	_blocs.reserve(WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ);


	genHeight();


	//calcule les visibilités des blocs
	calcVisibility();

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
}

void World::touche(int key, int scancode, int action, int mods)
{
	_player->toucheJoueur(key, scancode, action, mods);
}

void World::draw()
{	
	_player->display();


	//soleil
	glPushMatrix();
		GLfloat alpha = fmod(glfwGetTime()*2, 360);
		glRotatef(alpha, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 200.0f, 0.0f);

		// glBegin(GL_QUADS);
		// 	glVertex3f(-0.5f, 0.5f, 0.0f);
		// 	glVertex3f(-0.5f, -0.5f, 0.0f);
		// 	glVertex3f(0.5f, -0.5f, 0.0f);
		// 	glVertex3f(0.5f, 0.5f, 0.0f);
		// glEnd();

		// if (alpha < 180)
		// {
		// 	double sinus = sin(alpha * M_PI/360.0f), cosinus = cos(alpha * M_PI/360.0f)/10.0f;

		// 	GLfloat lum_amb[] = {sinus*0.2f + cosinus, sinus*0.2f, sinus*0.2f, 1.0f};
		// 	GLfloat lum_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
		// 	GLfloat lum_dif[] = {sinus*0.7f + cosinus, sinus*0.7f, sinus*0.7f, 1.0f};

		// 	glLightfv(GL_LIGHT3, GL_POSITION, lum_pos);
		// 	glLightfv(GL_LIGHT3, GL_AMBIENT , lum_amb);
		// 	glLightfv(GL_LIGHT3, GL_DIFFUSE, lum_dif);
		// 	glLightfv(GL_LIGHT3, GL_SPECULAR, lum_dif);

		// 	glEnable(GL_LIGHT3);
		// }
		// else
		// {
		// 	GLfloat lum_amb[] = {0.2f, 0.2f, 0.3f, 1.0f};
		// 	GLfloat lum_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
		// 	GLfloat lum_dif[] = {0.2f, 0.2f, 0.4f, 1.0f};

		// 	glLightfv(GL_LIGHT3, GL_POSITION, lum_pos);
		// 	glLightfv(GL_LIGHT3, GL_AMBIENT , lum_amb);
		// 	glLightfv(GL_LIGHT3, GL_DIFFUSE, lum_dif);
		// 	glLightfv(GL_LIGHT3, GL_SPECULAR, lum_dif);

		// 	glEnable(GL_LIGHT3);
		// }

		GLfloat lum_amb[] = {0.4f, 0.4f, 0.4f, 1.0f};
		GLfloat lum_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat lum_dif[] = {0.6f, 0.6f, 0.6f, 1.0f};

		glLightfv(GL_LIGHT3, GL_POSITION, lum_pos);
		glLightfv(GL_LIGHT3, GL_AMBIENT , lum_amb);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, lum_dif);
		glLightfv(GL_LIGHT3, GL_SPECULAR, lum_dif);

		glEnable(GL_LIGHT3);




	glPopMatrix();


	static std::vector<int> v;

	//affiche les blocs du monde
	if (_listId)
	{
		glCallList(_listId);


		//affichage des blocs transparents trouvés lors du premier parcours du monde
		_renderer->clean();
		_renderer->setActiveTex(Cube::_texId[1]);
		_renderer->setBlending(true);


		for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i)
		{
			_renderer->setTranslation((*i)%WORLDSIZEX,((*i)/WORLDSIZEX)%WORLDSIZEY,  (*i)/(WORLDSIZEX*WORLDSIZEY));
			_blocs[*i]->display();
		}

		_renderer->display();

		Water::inc();
	}
	else
	{
		_listId = glGenLists(1);

		glNewList(_listId, GL_COMPILE_AND_EXECUTE);



			//parcour du monde, affichage des blocs non transparents, stockage des blocs transparent dans un vector temporaire pour un affichage plus tard

			v.clear();
			_renderer->clean();
			_renderer->setActiveTex(Cube::_texId[0]);
			_renderer->setBlending(false);

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

	}
	

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
					somme += map[x-demiEspace + (y-demiEspace)*WORLDSIZEX];
					n++;
				}

				if ((x-demiEspace >= 0) && (y+demiEspace < WORLDSIZEY))
				{
					somme += map[x-demiEspace + (y+demiEspace)*WORLDSIZEX];
					n++;
				}
				
				if ((x+demiEspace < WORLDSIZEX) && (y+demiEspace < WORLDSIZEY))
				{
					somme += map[x+demiEspace + (y+demiEspace)*WORLDSIZEX];
					n++;
				}
				
				if ((x+demiEspace < WORLDSIZEX) && (y-demiEspace >= 0))
				{
					somme += map[x+demiEspace + (y-demiEspace)*WORLDSIZEX];
					n++;
				}


				map[x + y*WORLDSIZEX] = somme/n + (((double)rand()/RAND_MAX)*2 - 1) * demiEspace * lissage;
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
					somme += map[x-demiEspace + y * WORLDSIZEX];
					n++;
				}

				if (y+demiEspace < WORLDSIZEY)
				{
					somme += map[x + (y+demiEspace)*WORLDSIZEX];
					n++;
				}
				
				if (x+demiEspace < WORLDSIZEX)
				{
					somme += map[x+demiEspace + (y)*WORLDSIZEX];
					n++;
				}
				
				if (y-demiEspace >= 0)
				{
					somme += map[x + (y-demiEspace)*WORLDSIZEX];
					n++;
				}


				map[x + y*WORLDSIZEX] = somme/n + (((double)rand()/RAND_MAX)*2 - 1) * demiEspace * lissage;
			}
		}

		espace = demiEspace;
	}



	for (int i = 0; i < WORLDSIZEX * WORLDSIZEY; ++i)
	{
		map[i] = round(map[i]);
		map[i] = (map[i] > WORLDSIZEZ) ? WORLDSIZEZ : map[i];
		map[i] = (map[i] < 0) ? 0 : map[i];
	}



	_blocs.reserve(WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ);
	//remplissage du monde en utilisant la map calculée précédément, les blocs de [0, map[x, y]-2] = (Stone 75%, Coal 25%), [map-1, map] = (Dirt, Grass si le bloc du dessus est vide)	
	for (int i = 0, x = 0, y = 0, z = 0; i < WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ; ++i)
	{
		if ((z == map[x + y * WORLDSIZEX]-1) || (z == map[x + y * WORLDSIZEX]))
		{
			c = new Dirt(63);
		}
		else if (z < map[x + y * WORLDSIZEX])
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
	long x, y, z;
	std::vector<Cube *>::iterator i;

	for (x = 0, y = 0, z = 0, i = _blocs.begin(); i != _blocs.end(); ++i)
	{
		if (*i)
		{			
			//une face est visible si elle n'est pas limite du monde, si le bloc au dessus/dessous/côté est un bloc d'air (NULL) ou transparent dans ce cas le bloc ne doit pas être transparent lui même
			(*i)->setVisibility(
					((x > 0) && (!_blocs[x-1 + WORLDSIZEX * y + WORLDSIZEY * WORLDSIZEX * z] || (_blocs[x-1 + WORLDSIZEX * y + WORLDSIZEY * WORLDSIZEX * z]->isTransparent() && !(*i)->isTransparent()))? BACK : 0)
				|
					((y > 0) && (!_blocs[x + WORLDSIZEX * (y-1) + WORLDSIZEY * WORLDSIZEX * z] || (_blocs[x + WORLDSIZEX * (y-1) + WORLDSIZEY * WORLDSIZEX * z]->isTransparent() && !(*i)->isTransparent()))? LEFT : 0)
				| 
					((z > 0) && (!_blocs[x + WORLDSIZEX * y + WORLDSIZEY * WORLDSIZEX * (z-1)] || (_blocs[x + WORLDSIZEX * y + WORLDSIZEY * WORLDSIZEX * (z-1)]->isTransparent() && !(*i)->isTransparent())) ? BOT : 0)
				|
					((x < WORLDSIZEX) && (!_blocs[x+1 + WORLDSIZEX * y + WORLDSIZEY * WORLDSIZEX * z] || (_blocs[x+1 + WORLDSIZEX * y + WORLDSIZEY * WORLDSIZEX * z]->isTransparent() && !(*i)->isTransparent())) ? FRONT : 0)
				| 
					((y < WORLDSIZEY) && (!_blocs[x + WORLDSIZEX * (y+1) + WORLDSIZEY * WORLDSIZEX * z] || (_blocs[x + WORLDSIZEX * (y+1) + WORLDSIZEY * WORLDSIZEX * z]->isTransparent() && !(*i)->isTransparent())) ? RIGHT : 0)
				| 
					((z < WORLDSIZEZ) && (!_blocs[x + WORLDSIZEX * y + WORLDSIZEY * WORLDSIZEX * (z+1)] || (_blocs[x + WORLDSIZEX * y + WORLDSIZEY * WORLDSIZEX * (z+1)]->isTransparent() && !(*i)->isTransparent())) ? TOP : 0)
				|
					(dynamic_cast<Water *>(*i) ? TRANSPARENT : 0)
				);
			if (((z < WORLDSIZEZ) && !_blocs[x + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * (z+1)]) && dynamic_cast<Dirt *>((*i)))
			{
				char vis = (*i)->getVisibility();
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
#include "world.hpp"

#include <cstdlib> //rand
#include <cmath>
#include <iostream>



World::World(Renderer * renderer):
_renderer(renderer)
{
	int x = 0, y = 0, z = 0;
	Objet::setRenderer(_renderer);
	_blocs.reserve(WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ);


	genHeight();


	//calculer les visibilités des blocs
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


void World::draw()
{
	for (std::vector<Cube *>::iterator i = _blocs.begin(); i != _blocs.end(); ++i)
	{
		if (*i)
		{
			(*i)->display();
		}
	}
}

void World::genHeight()
{
	float lissage = 0.5f;
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


	for (int i = 0; i < WORLDSIZEX; ++i)
	{
		for (int j = 0; j < WORLDSIZEY; ++j)
		{
			std::cout << map[i + j*WORLDSIZEX] << " ";
		}
		std::cout << std::endl;
	}


	for (int i = 0; i < WORLDSIZEX * WORLDSIZEY; ++i)
	{
		map[i] = round(map[i]);
		map[i] = (map[i] > WORLDSIZEZ) ? WORLDSIZEZ : map[i];
		map[i] = (map[i] < 0) ? 0 : map[i];
	}


	for (int i = 0; i < WORLDSIZEX; ++i)
	{
		for (int j = 0; j < WORLDSIZEY; ++j)
		{
			std::cout << map[i + j*WORLDSIZEX] << " ";
		}
		std::cout << std::endl;
	}


	_blocs.reserve(WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ);
	//remplissage du monde en utilisant la map calculée précédément, les blocs de [0, map[x, y]-2] = (Stone 75%, Coal 25%), [map-1, map] = (Dirt, Grass si le bloc du dessus est vide)	
	for (int i = 0, x = 0, y = 0, z = 0; i < WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ; ++i)
	{
		if ((z == map[x + y * WORLDSIZEX]-1) || (z == map[x + y * WORLDSIZEX]))
		{
			c = new Dirt(1.0f, 63);
			c->setTranslation(x, y, z);
		}
		else if (z < map[x + y * WORLDSIZEX])
		{
			if (rand()%4)
			{
				c = new Coal(1.0f, 63);
			}
			else
			{
				c = new Stone(1.0f, 63);
			}
			c->setTranslation(x, y, z);
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

}

void World::calcVisibility()
{
	int x, y, z;
	std::vector<Cube *>::iterator i;

	for (x = 0, y = 0, z = 0, i = _blocs.begin(); i != _blocs.end(); ++i)
	{
		if (*i)
		{			
			(*i)->setVisibility(
					((x > 0) && !_blocs[x-1 + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * z] ? BACK : 0)
				|
					((y > 0) && !_blocs[x + WORLDSIZEY * (y-1) + WORLDSIZEY * WORLDSIZEX * z] ? LEFT : 0)
				| 
					((z > 0) && !_blocs[x + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * (z-1)] ? BOT : 0)
				|
					((x < WORLDSIZEX) && !_blocs[x+1 + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * z] ? FRONT : 0)
				| 
					((y < WORLDSIZEY) && !_blocs[x + WORLDSIZEY * (y+1) + WORLDSIZEY * WORLDSIZEX * z] ? RIGHT : 0)
				| 
					((z < WORLDSIZEZ) && !_blocs[x + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * (z+1)] ? TOP : 0)
				);
			if (((z < WORLDSIZEZ) && !_blocs[x + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * (z+1)]) && dynamic_cast<Dirt *>((*i)))
			{
				char vis = (*i)->getVisibility();
				delete *i;
				*i = new Grass(1.0f, vis);
				(*i)->setTranslation(x, y, z);
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
#include "world.hpp"



World::World(Renderer * renderer):
_renderer(renderer)
{
	int x, y, z = 0;

	_blocs.reserve(WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ);

	//repmplir le monde
	for (int i = 0; i < WORLDSIZEX * WORLDSIZEY * WORLDSIZEZ; ++i)
	{
		Cube * c = NULL;
		if (z < 30)
		{
			if (rand() % 3)
			{
				c = new Stone();
				c->setTranslation(x, y, z);

			}
			else
			{
				c = new Coal();
				c->setTranslation(x, y, z);
			}
		}
		else if (z < 50)
		{
			if (rand() % 5)
			{ 
				c = new Dirt();
				c->setTranslation(x, y, z);
			}
			else
			{
				c = new Stone();
				c->setTranslation(x, y, z);
			}
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

	//calculer les visibilités des blocs

	std::vector<Cube *>::iterator i;
	for (x = 0, y = 0, z = 0, i = _blocs.begin(); i != _blocs.end(); ++i)
	{
		if (*i)
		{			
			(*i)->setVisibility(
					((x == 0) || !_blocs[x-1 + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * z] ? BACK : 0)
				|
					((y == 0) || !_blocs[x + WORLDSIZEY * (y-1) + WORLDSIZEY * WORLDSIZEX * z] ? LEFT : 0)
				| 
					((z == 0) || !_blocs[x + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * (z-1)] ? BOT : 0)
				|
					((x == WORLDSIZEX-1) || !_blocs[x+1 + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * z] ? FRONT : 0)
				| 
					((y == WORLDSIZEY-1) || !_blocs[x + WORLDSIZEY * (y+1) + WORLDSIZEY * WORLDSIZEX * z] ? RIGHT : 0)
				| 
					((z == WORLDSIZEZ-1) || !_blocs[x + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * (z+1)] ? TOP : 0)
				);

			if (((z == WORLDSIZEZ-1) || !_blocs[x + WORLDSIZEY * y + WORLDSIZEY * WORLDSIZEX * (z+1)]) && dynamic_cast<Dirt *>((*i)))
			{
				char vis = (*i)->getVisibility();
				delete *i;
				*i = new Grass(1.0f, vis);
				(*i)->setTranslation(x, y, z);
			}
		}

//


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
			(*i)->setRenderer(_renderer);
			(*i)->display();
		}

	}
}
#include "player.hpp"

#include <iostream>
#include <cstdlib>

Vect3D Player::_gravity(0.0f, 0.0f, 0.02f);


Player::Player(World * w):Luciole(w), _world(w), _fly(false), _v(0.0f,0.0f,0.0f), _jump(false), _espace_presse(false)
{
	spawn();
}

Player::~Player(){}

void Player::spawn()
{
	int x = rand() % WORLDSIZEX, y = rand() % WORLDSIZEY, z = _world->hauteur(x, y) + 3.0f;

	_eye(x, y, z);

}

void Player::draw()
{
	Luciole::_phi = -Camera::_phi;
	Luciole::_theta = Camera::_theta + 180.0f;

	_pos = _center + Vect3D(0.0f, -LUCIOLE_WIDTH/2.0f, -0.2f);

	Luciole::draw();
}


void Player::toucheJoueur(int key, int action)
{
	switch (key) {
        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            _gauche_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            _avant_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            _droite_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            _arriere_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_PAGE_UP:
        case GLFW_KEY_Q:
            _haut_presse  = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_PAGE_DOWN:
        case GLFW_KEY_Z:
            _bas_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_SPACE:
	        if (!_jump)
	        {
				_v(0.0f, 0.0f, 0.4f);
				_jump = true;
			}
        break;

        case GLFW_KEY_R:
        	if (action == GLFW_PRESS)
        	{
        		_fly = !_fly;
        	};
        break;
    }
}

void 	Player::move()
{
	if (_fly)
	{
		Camera::move();
	}
	else
	{
		Vect3D av(cos(Camera::_theta * M_PI/180), sin(Camera::_theta * M_PI/180), 0.0f);
		av.normalize();
		Vect3D s =  _haut * av;
		s.normalize();

		Vect3D pied = _eye - Vect3D(0.0f, 0.0f, 1.8f);

		if (!_v)
		{
			if (_world->empty(pied - _gravity))
			{
				_v -= _gravity;
			}
		}
		else
		{
			if (_world->empty(pied + _v))
			{
				pied += _v;
				_v -= _gravity;
			}
			else
			{
				_v(0.0f, 0.0f, 0.0f);
				_jump = false;
				pied[3] = _world->hauteur(static_cast<unsigned int>(pied[0]), static_cast<unsigned int>(pied[1]));
			}
		}

		_eye = pied + Vect3D(0.0f, 0.0f, 1.8f);


		if (_avant_presse && _world->empty(pied + av * _vitesse))
		{
			_eye += av * _vitesse;
		}
		if (_gauche_presse && _world->empty(pied + s * _vitesse))
		{
			_eye += s * _vitesse;
		}
		if (_arriere_presse && _world->empty(pied - av * _vitesse))
		{
			_eye -= av * _vitesse;
		}
		if (_droite_presse && _world->empty(pied - s * _vitesse))
		{
			_eye -= s * _vitesse;
		}
		if (_haut_presse && _world->empty(pied + _haut * _vitesse))
		{
			_eye += _haut * _vitesse;
		}
		if (_bas_presse && _world->empty(pied - _haut * _vitesse))
		{			
			_eye -= _haut * _vitesse;
		}

		_center = _eye + _avant;

	}
}

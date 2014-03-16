#include "player.hpp"

Player::Player(World * w):Camera(-20, -20, 80), _world(w), _fly(true), _v(0.0f,0.0f,0.0f), _jump(false){}
Player::~Player(){}



void Player::toucheJoueur(int key, int scancode, int action, int mods)
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
            go(5,5,0);
            _phi = 0.0f;
            _theta = 180.0f;
            vectorFromAngle();
        break;

        case GLFW_KEY_R:
        	if (action == GLFW_PRESS)
        	{
        		_fly = !_fly;
        	};
        break;
    }
}
//TODO
void 	Player::move()
{
	if (_fly)
	{
		Camera::move();
	}
	else
	{
		Vect3D av(cos(_theta * M_PI/180), sin(_theta * M_PI/180), 0.0f), s =  _haut * av;

		if (_avant_presse)
		{
			_eye = _eye + av * _vitesse;
		}
		if (_gauche_presse)
		{
			_eye = _eye + s * _vitesse;
		}
		if (_arriere_presse)
		{
			_eye = _eye - av * _vitesse;
		}
		if (_droite_presse)
		{
			_eye = _eye - s * _vitesse;
		}
		if (_haut_presse)
		{
			_eye = _eye + _haut * _vitesse;
		}
		if (_bas_presse)
		{
			_eye = _eye - _haut * _vitesse;
		}
//TODO à améliorer
		//on check si on la caméra entre sous la surface, modifie la position et retourne true si modifé
		if(_eye[2] -1.8f < _world->hauteur(_eye[0], _eye[1]))
		{
			_eye = _eye + _haut*1.8f;
		}



		_center = _eye + _avant;

	}
}
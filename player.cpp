#include "player.hpp"

Player::Player():Camera(-20, -20, 80){}
Player::~Player(){}



void Player::toucheJoueur(int key, int scancode, int action, int mods)
{
	switch (key) {
        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            gauche_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            avant_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            droite_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            arriere_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_PAGE_UP:
        case GLFW_KEY_Q:
            haut_presse  = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_PAGE_DOWN:
        case GLFW_KEY_Z:
            bas_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_SPACE:
            go(5,5,0);
            phi = 0.0f;
            theta = 180.0f;
            vectorFromAngle();
        break;
    }
}
#include "camera.hpp"
#include <cmath>


Camera::Camera( GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ):
    eye(eyeX, eyeY, eyeZ),
    phi(0), theta(0), haut(0,0,1), 
    avant_presse(false), arriere_presse(false), gauche_presse(false), droite_presse(false), haut_presse(false), bas_presse(false),
    vitesse(0.30f)
{
    vectorFromAngle();
}

void Camera::move()
{

    if (avant_presse)
    {
        eye = eye + avant * vitesse;
    }
    if (gauche_presse)
    {
        eye = eye + gauche * vitesse;
    }
    if (arriere_presse)
    {
        eye = eye - avant * vitesse;
    }
    if (droite_presse)
    {
        eye = eye - gauche * vitesse;
    }
    if (haut_presse)
    {
        eye = eye + haut * vitesse;
    }
    if (bas_presse)
    {
        eye = eye - haut * vitesse;
    }


    center = eye + avant;
}

void Camera::go(GLdouble x, GLdouble y, GLdouble z)
{
    eye.set(x, y, z);
    center = eye + avant;
}

void Camera::vectorFromAngle()
{
    static Vect3D up(0.0f,0.0f,1.0f);

    if (phi > 89)
    {
        phi = 89.0f;
    }
    else if (phi < -89)
    {
        phi = -89;
    }


    double tmp = cos(phi * M_PI/180);


    avant.set(tmp * cos(theta * M_PI/180), tmp * sin(theta * M_PI/180), sin(phi * M_PI/180));
    avant.normalize();

    gauche = up * avant;
    gauche.normalize();

    center = eye + avant;
}

void Camera::display()
{
    move();
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear The Screen And The Depth Buffer
    glLoadIdentity();


    //calcul de la matrice de gluLookAt (deprecated)
    Vect3D up = -gauche * avant;

    GLfloat M[] =
    {
        -gauche[0], up[0], -avant[0], 0.0f,
        -gauche[1], up[1], -avant[1], 0.0f,
        -gauche[2], up[2], -avant[2], 0.0f,
        0.0f, 0.0f, 0.0f,  1.0f
    };

    glMultMatrixf(M);
    glTranslated(-eye[0], -eye[1], -eye[2]);

}

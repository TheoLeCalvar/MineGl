#include "camera.hpp"
#include <cmath>

Camera * Camera::_activeCamera = NULL;

Camera::Camera( GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ):
    eye(eyeX, eyeY, eyeZ),
    phi(0), theta(0), haut(0,0,1), 
    avant_presse(false), arriere_presse(false), gauche_presse(false), droite_presse(false), haut_presse(false), bas_presse(false),
    vitesse(0.30f)
{
    if (!_activeCamera)
    {
        _activeCamera = this;
    }
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

void Camera::mouse_event(GLFWwindow * w, double x, double y)
{
    int width, height;
    glfwGetWindowSize(w, &width, &height);
    width /= 2;
    height /= 2;


    if ((x - width != 0) ||  (y - height != 0))
    {

        _activeCamera->theta    -= (x - width)*0.2f;
        _activeCamera->phi      -= (y - height)*0.2f;

        _activeCamera->vectorFromAngle();

        #ifdef __APPLE__    
            int xpos, ypos;
            glfwGetWindowPos(w, &xpos, &ypos);

            CGPoint warpPoint = CGPointMake(width + xpos, height + ypos);
            CGWarpMouseCursorPosition(warpPoint);
            CGAssociateMouseAndMouseCursorPosition(true);
        #else
            glfwSetCursorPos (w, width, height);
        #endif
    }
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

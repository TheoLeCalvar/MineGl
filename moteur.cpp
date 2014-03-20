#include "moteur.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>


Moteur   * Moteur::_mot = NULL;
Renderer * Moteur::_renderer = NULL;

Moteur * Moteur::create()
{
    if (_mot)
    {
        return NULL;
    }
    _mot = new Moteur();

    return _mot;
}

Moteur::Moteur()
{
    glfwInit();

    _window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

    glfwMakeContextCurrent(_window);



    init_scene();


    glfwSetKeyCallback(_window, Moteur::keyboard_handler);
    glfwSetCursorPosCallback(_window, Camera::mouse_event);


    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos (_window, 400, 300);
}

void Moteur::destroy()
{
    delete _mot;
}

Moteur::~Moteur()
{
    _mot = NULL;

    delete _world;
    _renderer->destroy();
}

void showFrame()
{
  static int nbFrame = 1;
  static double temps = 0;


  if (glfwGetTime() - temps > 1.0f)
  {
    std::cout << "Fps : "<< nbFrame << std::endl;
    nbFrame = 0;
    temps = glfwGetTime();

  }
  else
  {
    ++nbFrame;
  }
}

void Moteur::start()
{
    int width, height;
    glfwGetWindowSize(_window, &width, &height);


    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_FOG);


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL); 


    glViewport(0,0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();



    //remplacement de gluPerspective, deprecated
    GLfloat angle = 45.0f;
    GLfloat f = 1.0f / tan((angle * (M_PI/180.0f))/2.0f);
    GLfloat zFar = 400.0f, zNear = 1.0f;
    GLfloat aspect = (GLdouble)width/(GLdouble)height;
    GLfloat perspective[] =
    {
        f/aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (zNear + zFar)/(zNear - zFar), -1.0f,
        0.0f, 0.0f, (2*zFar*zNear)/(zNear - zFar), 0.0f
    };

    glMultMatrixf(perspective);


    glMatrixMode(GL_MODELVIEW);

    //boucle d'affichage
    while(!glfwWindowShouldClose(_window))
    {

        glBegin(GL_QUADS);

            glColor3ub(125, 10, 14);
            glVertex3i(-100, -100, -10);
            glVertex3i(100, -100, -10);
            glVertex3i(100, 100, -10);
            glVertex3i(-100, 100, -10);

        glEnd();

        _world->draw();




        glfwSwapBuffers(_window);
        glfwPollEvents();

        showFrame();
    }

    glfwDestroyWindow(_window);

    glfwTerminate();

}



void Moteur::keyboard_handler(GLFWwindow *, int key, int, int action, int)
{
    switch (key) {

        case GLFW_KEY_A:
        case GLFW_KEY_W:
        case GLFW_KEY_D:
        case GLFW_KEY_S:
        case GLFW_KEY_Q:
        case GLFW_KEY_Z:
        case GLFW_KEY_R:
        case GLFW_KEY_UP:
        case GLFW_KEY_LEFT:
        case GLFW_KEY_RIGHT:
        case GLFW_KEY_DOWN:
        case GLFW_KEY_PAGE_UP:
        case GLFW_KEY_PAGE_DOWN:
        case GLFW_KEY_SPACE:
            _mot->_world->touche(key, action);
        break;

        case GLFW_KEY_ESCAPE: 
            glfwSetWindowShouldClose(_mot->_window, GL_TRUE);                 
        break; 


        case GLFW_KEY_1: 
            if (action == GLFW_PRESS)
            {
                _mot->switch_light();
            }
        break;

        case GLFW_KEY_2:
            if (action == GLFW_PRESS)
            {
                _mot->switch_cullface();
            }
        break;

        case GLFW_KEY_3:
            if (action == GLFW_PRESS)
            {
                _mot->switch_wire();
            }
        break;

        default:
        std::cout << "Key pressed " << key << std::endl;
    }
}

void Moteur::switch_light() 
{ 
    static bool light = true;

    if (!light) {
        glDisable(GL_LIGHTING); 
    } else {
        glEnable(GL_LIGHTING);
    }
    light = !light;
}

void Moteur::switch_cullface() 
{ 
    static bool light = false;

    if (!light) {
        glDisable(GL_CULL_FACE); 
    } else {
        glEnable(GL_CULL_FACE);
    }
    light = !light;
}

void Moteur::switch_wire()
{
    static bool wire = true;

    if (wire)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    else
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    wire = !wire;
}

void  Moteur::init_scene()
{
    _renderer = Renderer::create();
    _world = new World(_renderer);
}




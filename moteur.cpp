#include "moteur.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>


Moteur   * Moteur::mot = NULL;
Renderer * Moteur::_renderer = NULL;

Moteur * Moteur::create()
{
    if (mot)
    {
        return NULL;
    }
    mot = new Moteur();

    return mot;
}

Moteur::Moteur()
{
    glfwInit();

    m_window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

    glfwMakeContextCurrent(m_window);



    init_scene();


    glfwSetKeyCallback(m_window, Moteur::keyboard_handler);
    glfwSetCursorPosCallback(m_window, Moteur::mouse_event);


    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos (m_window, 400, 300);
}

Moteur::~Moteur()
{
    mot = NULL;
}

void showFrame()
{
  static int nbFrame = 0;
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
    glfwGetWindowSize(mot->m_window, &width, &height);


    glClearColor(0,0,0,0);
    glDepthFunc(GL_LEQUAL); 
    glShadeModel(GL_SMOOTH);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);



    glViewport(0,0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();



    //remplacement de gluPerspective, deprecated
    GLfloat angle = 45.0f;
    GLfloat f = 1.0f / tan((angle * (M_PI/180.0f))/2.0f);
    GLfloat zFar = 200.0f, zNear = 1.0f;
    GLfloat aspect = (GLdouble)width/(GLdouble)height;
    GLfloat perspective[] =
    {
        f/aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (zNear + zFar)/(zNear - zFar), -1.0f,
        0.0f, 0.0f, (2*zFar*zNear)/(zNear - zFar), 0.0f
    };

    glMultMatrixf(perspective);

    // gluPerspective(angle, aspect, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);


    while(!glfwWindowShouldClose(m_window))
    {
        
        mot->m_camera->display(); 

        glBegin(GL_QUADS);

            glColor3ub(125, 10, 14);
            glVertex3i(-100, -100, -10);
            glVertex3i(100, -100, -10);
            glVertex3i(100, 100, -10);
            glVertex3i(-100, 100, -10);

        glEnd();
        // for (std::vector<Objet *>::iterator i = mot->m_listeObjet.begin(); i != mot->m_listeObjet.end(); ++i)
        // {
        //     (*i)->setRenderer(_renderer);
        //     (*i)->display();
        // }
        _world->draw();

        _renderer->display();


        mot->lumiere();

        _renderer->clean();

        glfwSwapBuffers(m_window);
        glfwPollEvents();

        showFrame();
    }

    glfwDestroyWindow(m_window);

    glfwTerminate();

    // for (std::vector<Objet *>::iterator i = m_listeObjet.begin(); i != m_listeObjet.end(); ++i)
    // {
    //     delete (*i);
    // }
    delete _world;
    delete m_camera;
    _renderer->destroy();
}

void Moteur::mouse_event(GLFWwindow *, double x, double y)
{
    int width, height;
    glfwGetWindowSize(mot->m_window, &width, &height);
    width /= 2;
    height /= 2;


    if ((x - width != 0) ||  (y - height != 0))
    {

        mot->m_camera->theta    -= (x - width)*0.2f;
        mot->m_camera->phi      -= (y - height)*0.2f;

        mot->m_camera->vectorFromAngle();

        #ifdef __APPLE__    
            int xpos, ypos;
            glfwGetWindowPos(mot->m_window, &xpos, &ypos);

            CGPoint warpPoint = CGPointMake(width + xpos, height + ypos);
            CGWarpMouseCursorPosition(warpPoint);
            CGAssociateMouseAndMouseCursorPosition(true);
        #else
            glfwSetCursorPos (mot->m_window, width, height);
        #endif
    }
}

void Moteur::keyboard_handler(GLFWwindow *, int key, int scancode, int action, int mods)
{
    switch (key) {
        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            mot->m_camera->gauche_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            mot->m_camera->avant_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            mot->m_camera->droite_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            mot->m_camera->arriere_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_PAGE_UP:
        case GLFW_KEY_Q:
            mot->m_camera->haut_presse  = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_PAGE_DOWN:
        case GLFW_KEY_Z:
            mot->m_camera->bas_presse = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
        break;

        case GLFW_KEY_ESCAPE: 
            glfwSetWindowShouldClose(mot->m_window, GL_TRUE);                 
        break; 

        case GLFW_KEY_SPACE:
            mot->m_camera->go(5,5,0);
            mot->m_camera->phi = 0.0f;
            mot->m_camera->theta = 180.0f;
            mot->m_camera->vectorFromAngle();
        break;

        case GLFW_KEY_1: 
            if (action == GLFW_PRESS)
            {
                mot->switch_blend();
            }
        break;

        case GLFW_KEY_2: 
            if (action == GLFW_PRESS)
            {
                mot->switch_light();
            }
        break;

        case GLFW_KEY_3:
            if (action == GLFW_PRESS)
            {
                mot->switch_cullface();
            }
        break;

        case GLFW_KEY_4:
            if (action == GLFW_PRESS)
            {
                mot->switch_wire();
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

void Moteur::switch_blend() 
{
    static bool blend = glIsEnabled(GL_BLEND);

    if (blend) {
        glDisable(GL_BLEND);              // Turn Blending Off
        glEnable(GL_DEPTH_TEST);          // Turn Depth Testing On
    } else {
        glEnable(GL_BLEND);               // Turn Blending On
        glDisable(GL_DEPTH_TEST);         // Turn Depth Testing Off
    }
    blend = !blend;
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

//TODO: passer à un modèle propre de la lumière
void Moteur::lumiere()
{
    GLfloat lum_amb[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lum_pos[] = {10.0f, -20.0f, 10.0f, 1.0f};
    GLfloat lum_dif[] = {0.8f, 0.8f, 0.8f, 1.0f};




    glLightfv(GL_LIGHT1, GL_POSITION, lum_pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT , lum_amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lum_dif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lum_dif);



    glEnable(GL_LIGHT1);
}

void  Moteur::init_scene()
{
    _renderer = Renderer::create();
    m_camera = new Camera(-2, -2, 0);

    _world = new World(_renderer);

    // int maxI = 100, maxJ = 100, maxK = 10, r;

    // Cube *c = new Stone(4.0f, 127);
    // m_listeObjet.push_back(c);
    // c = new Grass(2.0f, 127);
    // c->setTranslation(2.0f, -1.0f, 0.0f);
    // m_listeObjet.push_back(c);
    // Cube * c;
    // for (int i = 0; i < maxI; ++i)
    // {
    //     for (int j = 0; j < maxJ; ++j)
    //     {
    //         for (int k = 0; k < maxK; ++k)
    //         {
    //             if ((r = rand())%4)
    //             {
    //                 c = new Grass(1.0f, (i==(maxI-1)), (j==(maxJ-1)), (i==0), (j==0), (k==(maxK-1)), (k==0));
    //             }
    //             else if (r %3)
    //             {
    //                 c = new Stone(1.0f, (i==(maxI-1)), (j==(maxJ-1)), (i==0), (j==0), (k==(maxK-1)), (k==0));
    //             }
    //             else
    //             {
    //                 c = new Coal(1.0f, (i==(maxI-1)), (j==(maxJ-1)), (i==0), (j==0), (k==maxK-1), (k==0));
    //             }
                
    //             c->setTranslation(i, j, k);
    //             m_listeObjet.push_back(c);
    //         }
    //     }
    // }
}




#include "Burden.h"
#include <GL/freeglut.h>
#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <iostream>


boost::signal<void ()> updateSignal;
boost::signal<void ()> displaySignal;
boost::signal<void (int, int)> reshapeSignal;
boost::signal<void (unsigned char, int, int)> keyboardSignal;
boost::signal<void (unsigned char, int, int)> keyboardUpSignal;
boost::signal<void (int, int, int, int)> mouseSignal;
boost::signal<void (int, int)> mouseMotionSignal;
boost::signal<void (int, int, int)> specialSignal;
boost::signal<void (int, int, int)> specialUpSignal;


const int updatePeriod = 10;


void update(int i)
{
    updateSignal();
    glutTimerFunc(updatePeriod, update, i);
    glutPostRedisplay();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    displaySignal();
    glutSwapBuffers();
}


void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    reshapeSignal(width, height);
}


void keyboard(unsigned char key, int x, int y)
{
    keyboardSignal(key, x, y);
}


void keyboardUp(unsigned char key, int x, int y)
{
    keyboardUpSignal(key, x, y);
}


void mouse(int button, int state, int x, int y)
{
    mouseSignal(button, state, x, y);
}


void mouseMotion(int x, int y)
{
    mouseMotionSignal(x, y);
}


void special(int key, int x, int y)
{
    specialSignal(key, x, y);
}


void specialUp(int key, int x, int y)
{
    specialUpSignal(key, x, y);
}


void startGlutApplication(std::string windowName, int windowWidth, int windowHeight)
{
    int argc = 0;
    char** argv = {};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(windowName.c_str());

    glutDisplayFunc(::display);
    glutReshapeFunc(::reshape);
    glutKeyboardFunc(::keyboard);
    glutKeyboardUpFunc(::keyboardUp);
    glutMouseFunc(::mouse);
    glutMotionFunc(::mouseMotion);
    glutSpecialFunc(::special);
    glutSpecialUpFunc(::specialUp);

    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, -1.0, 1.0);

    glutTimerFunc(updatePeriod, ::update, 0);
    glutMainLoop();
}


Burden::Burden()
{
    updateSignal.connect(boost::bind(&Burden::update, this));
    displaySignal.connect(boost::bind(&Burden::display, this));
    reshapeSignal.connect(boost::bind(&Burden::reshape, this, _1, _2));
    keyboardSignal.connect(boost::bind(&Burden::keyboard, this, _1, _2, _3));
    keyboardUpSignal.connect(boost::bind(&Burden::keyboardUp, this, _1, _2, _3));
    mouseSignal.connect(boost::bind(&Burden::mouse, this, _1, _2, _3, _4));
    mouseMotionSignal.connect(boost::bind(&Burden::mouseMotion, this, _1, _2));
    specialSignal.connect(boost::bind(&Burden::special, this, _1, _2, _3));
    specialUpSignal.connect(boost::bind(&Burden::specialUp, this, _1, _2, _3));
}


void Burden::run(std::string windowName, int windowWidth, int windowHeight)
{
    startGlutApplication(windowName, windowWidth, windowHeight);
}


void Burden::quit()
{
    glutLeaveMainLoop();
}

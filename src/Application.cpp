#include "Application.h"
#include <GL/freeglut.h>
#include <stdio.h> // for demo


Scene Application::_scene;
const int updatePeriod = 10;
int Application::_lastUpdateTime = 0;
int Application::_width = 800;
int Application::_height = 600;


void Application::exit()
{
    _scene.writeUsedTime();
    glutLeaveMainLoop();
}


void Application::registerCallbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
}

void Application::run(int argc, char** argv)
{
    _scene.load(argc, argv);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(_width, _height);
    glutCreateWindow("app");

    registerCallbacks();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-_width / 2, _width / 2, -_height / 2, _height / 2, -1.0, 1.0);

    glutTimerFunc(updatePeriod, update, 0);
    glutMainLoop();
}


void Application::update(int i)
{
    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = (elapsedTime - _lastUpdateTime) / 1000.0f;
    _lastUpdateTime = elapsedTime;

    // update
    _scene.update(dt);

    glutTimerFunc(updatePeriod, update, 0);
    glutPostRedisplay();
}


void Application::display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    // draw
    _scene.draw(_width, _height);

    glutSwapBuffers();
}


void Application::reshape(int width, int height)
{
    _width = width;
    _height = height;
    glViewport(0, 0, (GLsizei) _width, (GLsizei) _height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-_width / 2, _width / 2, -_height / 2, _height / 2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Application::keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
	case 27:
	    exit();
	    break;
	case 'p':
	    _scene.togglePause();
	    break;
	default:
	    break;
    }
}


void Application::keyboardUp(unsigned char key, int x, int y)
{
}


void Application::mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
	if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
	{
	    _scene.addAtom(Vector(x - _width / 2, - y + _height / 2));
	}
    }
}


void Application::motion(int x, int y)
{
}


void Application::special(int key, int x, int y)
{
}


void Application::specialUp(int key, int x, int y)
{
}

#include "Application.h"
#include <GL/freeglut.h>
#include "rangedRandom.h"
#include <stdio.h> // for demo purposes


const int updatePeriod = 10;
int Application::_lastUpdateTime = 0;
int Application::_width = 800;
int Application::_height = 600;


void Application::exit()
{
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
	int dt = elapsedTime - _lastUpdateTime;
	_lastUpdateTime = elapsedTime;

	// update

	glutTimerFunc(updatePeriod, update, 0);
	glutPostRedisplay();
}


void Application::display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);

	// draw

	// demo
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	glVertex2f(_width/2, _height/2);
	glVertex2f(-_width/2, -_height/2);
	glVertex2f(-_width/2, _height/2);
	glVertex2f(_width/2, -_height/2);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	char resolution[12];
	sprintf(resolution, "%d x %d", _width, _height);
	glPushMatrix();
	glTranslatef(-_width/2, -_height/2, 0.0f);
	glScalef(0.2f, 0.2f, 1.0f);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*) resolution);
	glPopMatrix();

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
	if (key == 27) exit();
}


void Application::keyboardUp(unsigned char key, int x, int y)
{
}


void Application::mouse(int button, int state, int x, int y)
{
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

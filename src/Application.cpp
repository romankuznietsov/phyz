#include "Application.h"
#include "GL/freeglut.h"
#include "random.h"


const Time updatePeriod(10);
Time Application::_lastUpdateTime = 0;


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
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("app");

	registerCallbacks();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-960.0, 960.0, -540.0, 540.0, -1.0, 1.0);

	glutTimerFunc(updatePeriod.toInt(), update, 0);
	glutMainLoop();
}


void Application::update(int i)
{
	Time elapsedTime = glutGet(GLUT_ELAPSED_TIME);
	Time dt = elapsedTime - _lastUpdateTime;
	_lastUpdateTime = elapsedTime;

	// update

	glutTimerFunc(updatePeriod.toInt(), update, 0);
	glutPostRedisplay();
}


void Application::display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);

	// draw
	glBegin(GL_POINTS);
	for(int i = 0; i < 3000; i++)
	{
		glVertex2f(random(-960, 960), random(-540, 540));
	}
	glEnd();

	glutSwapBuffers();
}


void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-960.0, 960.0, -540.0, 540.0, -1.0, 1.0);
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

#include "Application.h"
#include <GL/freeglut.h>


Application::Application(ScenePtr scene) :
    _lastUpdateTime(0),
    _scene(scene)
{}


Application::~Application()
{
    delete _scene;
}


void Application::update()
{
    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = (elapsedTime - _lastUpdateTime) / 1000.0f;
    _lastUpdateTime = elapsedTime;
    _scene->update(dt);
}


void Application::display()
{
    _scene->draw(_width, _height);
}


void Application::reshape(int width, int height)
{
    _width = width;
    _height = height;
}


void Application::keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
	case 27:
	    quit();
	    break;
	case 'p':
	    _scene->togglePause();
	    break;
	default:
	    break;
    }
}

#include "Application.h"
#include <GL/freeglut.h>


Application::Application(ModelPtr model) :
    _lastUpdateTime(0),
    _model(model)
{}


Application::~Application()
{
    delete _model;
}


void Application::update()
{
    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = (elapsedTime - _lastUpdateTime) / 1000.0f;
    _lastUpdateTime = elapsedTime;
    _model->update(dt);
}


void Application::display()
{
    _model->draw(_width, _height);
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
	    _model->togglePause();
	    break;
	default:
	    break;
    }
}

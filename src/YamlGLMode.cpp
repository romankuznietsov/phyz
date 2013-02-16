#include "YamlGLMode.h"
#include <GL/freeglut.h>


YamlGLMode::YamlGLMode() : _paused(true), _dt(0.005f)
{

}


void YamlGLMode::setDt(float dt)
{
    _dt = dt;
}


void YamlGLMode::loadFile(std::string yamlFileName)
{
    _model.loadFile(yamlFileName);
}


void YamlGLMode::update()
{
    if (!_paused)
	_model.update(_dt);
}


void YamlGLMode::display()
{
    _model.draw(_windowWidth, _windowHeight);
}


void YamlGLMode::keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
	case 27:
	    quit();
	    break;
	case 'p':
	    _paused = !_paused;
	    break;
	default:
	    break;
    }
}


void YamlGLMode::reshape(int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;
}

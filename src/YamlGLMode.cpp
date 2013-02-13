#include "YamlGLMode.h"
#include <GL/freeglut.h>


const float dt = 0.005f;


YamlGLMode::YamlGLMode() : _model(true)
{

}


void YamlGLMode::loadFile(std::string yamlFileName)
{
    _model.loadFile(yamlFileName);
}


void YamlGLMode::update()
{
    _model.update(dt);
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
	    _model.togglePause();
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

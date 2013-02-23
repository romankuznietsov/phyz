#include "YamlGLMode.h"
#include <GL/freeglut.h>
#include "YamlLoader.h"
#include "stdio.h"


YamlGLMode::YamlGLMode() : _paused(true)
{

}


void YamlGLMode::loadFile(std::string inputFileName)
{
    YamlLoader().load(inputFileName, _model);
}


void YamlGLMode::update()
{
    if (!_paused)
	_model.update();
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

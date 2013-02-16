#include "PhyGLMode.h"
#include <GL/freeglut.h>


PhyGLMode::PhyGLMode() : _paused(true)
{

}


void PhyGLMode::loadFile(std::string phyFileName)
{
    if (!_player.loadFile(phyFileName) || !_player.nextFrame())
	quit();
}


void PhyGLMode::update()
{
    if (!_paused && !_player.nextFrame())
	quit();
}


void PhyGLMode::display()
{
    _player.display(_windowWidth, _windowHeight);
}


void PhyGLMode::keyboard(unsigned char key, int x, int y)
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


void PhyGLMode::reshape(int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;
}

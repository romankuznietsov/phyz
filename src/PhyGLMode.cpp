#include "PhyGLMode.h"


PhyGLMode::PhyGLMode() : _glWindow(new GLWindow)
{

}


PhyGLMode::~PhyGLMode()
{
    delete _glWindow;
}


void PhyGLMode::loadFile(std::string phyFileName)
{
    _loader.load(phyFileName);
    _loader.nextFrame();
}


void PhyGLMode::run()
{
    boost::thread glThread(GLWindow::glThreadFunc, _glWindow);
    _glWindow->setAtomColors(_loader.getAtomColors());
    do
    {
	_glWindow->setAtomPositions(_loader.getAtomPositions());
	_glWindow->waitForDisplay();
    }
    while(_loader.nextFrame());
    glThread.interrupt();
}

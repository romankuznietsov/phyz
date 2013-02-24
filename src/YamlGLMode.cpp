#include "YamlGLMode.h"
#include "YamlLoader.h"


YamlGLMode::YamlGLMode() : _glWindow(new GLWindow)
{

}


YamlGLMode::~YamlGLMode()
{
    delete _glWindow;
}


void YamlGLMode::loadFile(std::string inputFileName)
{
    YamlLoader().load(inputFileName, _model);
}


void YamlGLMode::run()
{
    boost::thread glThread(GLWindow::glThreadFunc, _glWindow);
    _glWindow->setAtomColors(_model.getAtomColors());
    while(true)
    {
	_model.update();
	_glWindow->setAtomPositions(_model.getAtomPositions());
	_glWindow->setLinkPositions(_model.getLinkPositions());
    }
    glThread.interrupt();
}

#include "YamlGLMode.h"
#include "YamlLoader.h"


void glThreadFunc(GLWindow* glWindow)
{
    glWindow->run();
}


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
    boost::thread glThread(glThreadFunc, _glWindow);
    _glWindow->setAtomColors(_model.getAtomColors());
    while(_model.time() < 3.0f)
    {
	_model.update();
	_glWindow->setAtomPositions(_model.getAtomPositions());
	_glWindow->setLinkPositions(_model.getLinkPositions());
    }
    glThread.interrupt();
}

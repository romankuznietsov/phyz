#ifndef YAML_GL_MODE_H
#define YAML_GL_MODE_H


#include "GLWindow.h"
#include <boost/thread.hpp>
#include <string>
#include "Model.h"


class YamlGLMode
{
    public:
	YamlGLMode();
	~YamlGLMode();
	void loadFile(std::string inputFileName);
	void run();

    private:
	Model _model;
	GLWindow* _glWindow;
};


#endif // YAML_GL_MODE_H

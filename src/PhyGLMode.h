#ifndef PHY_GL_MODE_H
#define PHY_GL_MODE_H


#include "burden/Burden.h"
#include "GLWindow.h"
#include "PhyLoader.h"
#include <boost/thread.hpp>
#include <string>


class PhyGLMode
{
    public:
	PhyGLMode();
	~PhyGLMode();
	void loadFile(std::string phyFileName);
	void run();

    private:
	PhyLoader _loader;
	GLWindow* _glWindow;
};


#endif // PHY_GL_MODE_H

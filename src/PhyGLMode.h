#ifndef PHY_GL_MODE_H
#define PHY_GL_MODE_H


#include "gxy/Gxy.h"
#include <string>


class PhyGLMode : public Gxy::Application
{
    public:
	PhyGLMode();
	void loadFile(std::string phyFileName);

    private:
	bool _paused;
};


#endif // PHY_GL_MODE_H

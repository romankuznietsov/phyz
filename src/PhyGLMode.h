#ifndef PHY_GL_MODE_H
#define PHY_GL_MODE_H


#include "gxy/Gxy.h"
#include "Player.h"
#include <string>


class PhyGLMode : public Gxy::Application
{
    public:
	PhyGLMode();
	void loadFile(std::string phyFileName);

    private:
	bool _paused;
	int _windowHeight;
	int _windowWidth;
	Player _player;
	void update();
	void display();
	void keyboard(unsigned char key, int x, int y);
	void reshape(int width, int height);
};


#endif // PHY_GL_MODE_H

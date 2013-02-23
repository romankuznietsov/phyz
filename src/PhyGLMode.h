#ifndef PHY_GL_MODE_H
#define PHY_GL_MODE_H


#include "burden/Burden.h"
#include "Player.h"
#include <string>


class PhyGLMode : public Burden
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

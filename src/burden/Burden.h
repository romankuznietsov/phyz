#ifndef GXY_H
#define GXY_H


#include <string>
#include <boost/signals/trackable.hpp>


class Burden : public boost::signals::trackable
{
    public:
	Burden();
	virtual ~Burden() {};
	void run(std::string windowName = "application", int windowWidth = 800, int windowHeight = 600);
	void quit();

	virtual void update() {};
	virtual void display() {};
	virtual void reshape(int, int) {};

	virtual void keyboard(unsigned char, int, int) {};
	virtual void keyboardUp(unsigned char, int, int) {};
	virtual void mouse(int, int, int, int) {};
	virtual void mouseMotion(int, int) {};
	virtual void special(int, int, int) {};
	virtual void specialUp(int, int, int) {};
};


#endif // GXY_H

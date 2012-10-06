#ifndef APPLICATION_H
#define APPLICATION_H


#include "Time.h"


class Application
{
	private:
		static Time _lastUpdateTime;

		static void exit();
		static void registerCallbacks();

		static void update(int i);
		static void display();
		static void reshape(int w, int h);

		static void keyboard(unsigned char key, int x, int y);
		static void keyboardUp(unsigned char key, int x, int y);
		static void mouse(int button, int state, int x, int y);
		static void motion(int x, int y);
		static void special(int key, int x, int y);
		static void specialUp(int key, int x, int y);
	public:
		static void run(int argc, char** argv);
};


#endif // APPLICATION_H

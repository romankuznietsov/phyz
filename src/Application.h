#ifndef APPLICATION_H
#define APPLICATION_H

#include "gxy/Gxy.h"
#include "Scene.h"


class Application : public Gxy::Application
{
    private:
	ScenePtr _scene;
	int _width;
	int _height;
	int _lastUpdateTime;
	void update();
	void display();
	void keyboard(unsigned char key, int x, int y);
	void reshape(int width, int height);

    public:
	Application(ScenePtr scene);
};


#endif // APPLICATION_H

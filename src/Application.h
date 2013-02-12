#ifndef APPLICATION_H
#define APPLICATION_H

#include "gxy/Gxy.h"
#include "Model.h"


class Application : public Gxy::Application
{
    private:
	ModelPtr _model;
	int _width;
	int _height;
	int _lastUpdateTime;
	void update();
	void display();
	void keyboard(unsigned char key, int x, int y);
	void reshape(int width, int height);

    public:
	Application(ModelPtr model);
	~Application();
};


#endif // APPLICATION_H

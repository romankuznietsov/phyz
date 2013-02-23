#ifndef YAML_GL_MODE_H
#define YAML_GL_MODE_H


#include "burden/Burden.h"
#include "Model.h"
#include <string>


class YamlGLMode : public Burden
{
    public:
	YamlGLMode();
	void loadFile(std::string inputFileName);

    private:
	bool _paused;
	int _windowHeight;
	int _windowWidth;
	Model _model;

	void update();
	void display();
	void keyboard(unsigned char key, int x, int y);
	void reshape(int width, int height);
};


#endif // YAML_GL_MODE_H

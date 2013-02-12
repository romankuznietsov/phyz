#ifndef SCENE_H
#define SCENE_H


#include "Objects.h"
#include <list>
#include <string>
#include <fstream>


class Model
{
    public:
	Model();
	void loadFile(std::string yamlFileName);
	void update(float dt);
	void draw(float width, float height);
	void writeProgress(std::ofstream outputFile);
	void togglePause();

    private:
	bool _paused;
	float _lastDt;
	Objects _objects;
};


typedef Model* ModelPtr;


#endif // SCENE_H
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
	void update();
	void draw(float width, float height);
	void writeHeader(std::ofstream& outputFile);
	void writeProgress(std::ofstream& outputFile);
	float dt();

    private:
	int _previousElapsedTime;
	float _dt;
	Objects _objects;
};


#endif // SCENE_H

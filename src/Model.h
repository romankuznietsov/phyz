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
	void writeProgress(std::ofstream& outputFile);

    private:
	float _lastDt;
	Objects _objects;
};


#endif // SCENE_H

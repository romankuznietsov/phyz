#ifndef SCENE_H
#define SCENE_H


#include "Objects.h"
#include <list>
#include <string>
#include <fstream>


class Scene
{
    private:
	bool _paused;
	float _lastDt;
	Objects _objects;
	std::list<float> _usedTime;
	std::ofstream _outputFile;
	void load(std::string inputFileName);

    public:
	Scene(std::string inputFileName);
	Scene(std::string inputFileName, std::string outputFileName);
	~Scene();
	void update(float dt);
	void draw(float width, float height);
	void writeProgress();

	void togglePause();
	void writeUsedTime();
};


typedef Scene* ScenePtr;


#endif // SCENE_H

#ifndef SCENE_H
#define SCENE_H


#include "Objects.h"
#include <list>
#include <string>


class Scene
{
    private:
	bool _paused;
	float _lastDt;
	Objects _objects;
	std::list<float> _usedTime;

    public:
	Scene(std::string inputFileName);
	void update(float dt);
	void draw(float width, float height);

	void togglePause();
	void writeUsedTime();
};


typedef Scene* ScenePtr;


#endif // SCENE_H

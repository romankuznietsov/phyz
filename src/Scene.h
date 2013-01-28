#ifndef SCENE_H
#define SCENE_H


#include "Objects.h"
#include <list>


class Scene
{
	private:
		bool _paused;
		float _lastDt;
		Objects _atoms;
		std::list<float> _usedTime;

	public:
		Scene();
		void update(float dt);
		void draw(float width, float height);

		void addAtom(Vector position);
		void addLink(Vector from, Vector to);
		void togglePause();
		void writeUsedTime();
};


#endif // SCENE_H

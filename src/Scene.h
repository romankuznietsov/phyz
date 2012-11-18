#ifndef SCENE_H
#define SCENE_H


#include "Atoms.h"


class Scene
{
	private:
		bool _paused;
		float _lastDt;
		Atoms _atoms;

	public:
		Scene();
		void update(float dt);
		void draw(float width, float height);

		void addAtom(Vector position);
		void addLink(Vector from, Vector to);
		void togglePause();
};


#endif // SCENE_H

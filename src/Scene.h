#ifndef SCENE_H
#define SCENE_H


#include "NewAtoms.h"


class Scene
{
	private:
		bool _paused;
		float _lastDt;
		NewAtoms _newAtoms;

	public:
		Scene();
		void update(float dt);
		void draw(float width, float height);

		void addAtom(Vector position);
		void addLink(Vector from, Vector to);
		void togglePause();
};


#endif // SCENE_H

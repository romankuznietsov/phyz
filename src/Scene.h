#ifndef SCENE_H
#define SCENE_H


#include "Atoms.h"
#include "Links.h"


class Scene
{
	private:
		bool _paused;
		float _lastDt;
		AtomsPtr _atoms;
		LinksPtr _links;
	public:
		Scene();
		void update(float dt);
		void draw(float width, float height);
		void addAtom(Vector position);
		void togglePause();
};

#endif // SCENE_H

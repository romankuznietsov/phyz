#ifndef SCENE_H
#define SCENE_H


#include "Atoms.h"
#include "Links.h"


class Scene
{
	private:
		AtomsPtr _atoms;
		LinksPtr _links;
	public:
		Scene();
		void update(float dt);
		void draw();
		void addAtom(Vector position);
};

#endif // SCENE_H

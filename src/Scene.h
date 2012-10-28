#ifndef SCENE_H
#define SCENE_H


#include "Atoms.h"


class Scene
{
	private:
		AtomsPtr _atoms;
		float _leftLimit;
		float _rightLimit;
		float _topLimit;
		float _bottomLimit;
	public:
		Scene();
		void update(float dt);
		void draw();
};

#endif // SCENE_H

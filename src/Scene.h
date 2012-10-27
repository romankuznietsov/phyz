#ifndef SCENE_H
#define SCENE_H


#include "AtomList.h"


class Scene
{
	private:
		AtomListPtr _atoms;
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

#ifndef SCENE_H
#define SCENE_H


#include "Vector.h"
#include "Color.h"
#include "Atom.h"
#include "Link.h"
#include "AtomIndex.h"
#include "Workers.h"
#include "DataObjects.h"
#include <vector>


class Model
{
    public:
	Model();
	void update();
	float time();
	void setDt(float dt);
	void addBody(Vector position, Vector size,  Vector speed, Color color,
		float density, float linkForce, float linkStretch,
		float linkDamping);
	DataObjects::Vectors getAtomPositions();
	DataObjects::VectorPairs getLinkPositions();
	DataObjects::Colors getAtomColors();

    private:
	float _dt;
	float _time;

	AtomIndexPtr _index;
	AtomPtrVector _atoms;
	LinkPtrVector _links;

	void updateCollisions();
	void updateLinks();
	void updateAtoms();
};


#endif // SCENE_H

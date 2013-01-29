#ifndef NEW_ATOMS_H
#define NEW_ATOMS_H


#include "Vector.h"
#include "Color.h"
#include <vector>
#include <utility>
#include "Atom.h"
#include "Link.h"
#include "AtomIndex.h"


class Objects
{
    private:
	AtomIndexPtr _index;
	AtomPtrVector _atoms;
	LinkPtrVector _links;

	void updateCollisions();
	void updateLinks();
	void updateAtomPositions();

    public:
	Objects();
	void draw();
	void update();

	void addBody(Vector from, Vector to,  Vector speed, Color color,
		float density = 20.0f, float linkForce = 1000.0f, float linkStretch = 1.5f);
};


#endif // NEW_ATOMS_H

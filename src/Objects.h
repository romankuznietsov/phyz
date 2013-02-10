#ifndef NEW_ATOMS_H
#define NEW_ATOMS_H


#include "Vector.h"
#include "Color.h"
#include <vector>
#include <utility>
#include "Atom.h"
#include "Link.h"
#include "AtomIndex.h"
#include "Workers.h"
#include <fstream>


class Objects
{
    private:
	AtomIndexPtr _index;
	AtomPtrVector _atoms;
	LinkPtrVector _links;
	std::ofstream _outputFile;

	void updateCollisions();
	void updateLinks();
	void updateAtoms();
	void writeAtomPositions();

    public:
	Objects();
	~Objects();
	void draw();
	void update();

	void addBody(Vector position, Vector size,  Vector speed, Color color,
		float density, float linkForce, float linkStretch, float linkDamping);
};


#endif // NEW_ATOMS_H

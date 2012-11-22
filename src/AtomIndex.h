#ifndef ATOM_INDEX_H
#define ATOM_INDEX_H


#include <map>
#include <unordered_set>
#include "Vector.h"


typedef std::unordered_set<unsigned int> AtomSet;
typedef std::map<float, AtomSet> CoordIndex;

class AtomIndex
{
	private:
		float _collisionDistance;
		CoordIndex _xIndex;
		CoordIndex _yIndex;

	public:
		AtomIndex(float atomRadius);
		void add(unsigned int atom, Vector position);
		void update(unsigned int atom, Vector oldPosition, Vector newPosition);
		AtomSet near(unsigned int atom, Vector position);
};


#endif // ATOM_INDEX_H

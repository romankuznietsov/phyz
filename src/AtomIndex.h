#ifndef ATOM_INDEX_H
#define ATOM_INDEX_H


#include "Vector.h"
#include <map>
#include <vector>


typedef std::vector<unsigned int> AtomVector;

class AtomIndex
{
	typedef std::multimap<float, unsigned int> SubIndex;
	typedef std::map<float, SubIndex> Index;
	private:
		float _atomDiameter;
		Index _index;

	public:
		AtomIndex(float atomRadius);
		void update(const std::vector<Vector>& positoins);
		AtomVector near(unsigned int atom, Vector position);
};


#endif // ATOM_INDEX_H

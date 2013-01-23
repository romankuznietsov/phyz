#ifndef ATOM_INDEX_H
#define ATOM_INDEX_H


#include <map>
#include <vector>
#include "Vector.h"


typedef std::vector<unsigned int> AtomVector;

class AtomIndex
{
	typedef std::multimap<int, unsigned int> SubIndex;
	typedef std::map<int, SubIndex> Index;
	private:
		float _atomDiameter;
		Index _index;
		int toIndex(float value);

	public:
		AtomIndex(float atomRadius);
		void update(const std::vector<Vector>& positoins);
		AtomVector near(unsigned int atom, Vector position);
};


#endif // ATOM_INDEX_H

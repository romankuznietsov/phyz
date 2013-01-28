#ifndef ATOM_INDEX_H
#define ATOM_INDEX_H


#include <map>
#include <vector>
#include "Vector.h"
#include "Atom.h"


class AtomIndex
{
	private:
		typedef std::vector<AtomPtrVector> SubIndex;
		typedef std::vector<SubIndex> Index;

		Index _index;
		unsigned int _cellNumber;
		int _indexOffset;
		unsigned int toIndex(float value);

	public:
		AtomIndex();
		void update(const AtomPtrVector& atoms);
		AtomPtrVector near(const AtomPtr& atom);
};


#endif // ATOM_INDEX_H

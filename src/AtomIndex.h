#ifndef ATOM_INDEX_H
#define ATOM_INDEX_H


#include <map>
#include <vector>
#include "Vector.h"


typedef std::vector<unsigned int> AtomVector;


class AtomIndex
{
	private:
		typedef std::vector<unsigned int> IndexCell;
		typedef std::vector<IndexCell> SubIndex;
		typedef std::vector<SubIndex> Index;

		float _atomDiameter;
		Index _index;
		unsigned int _cellNumber;
		int _indexOffset;
		unsigned int toIndex(float value);

	public:
		AtomIndex(float atomRadius);
		void update(const std::vector<Vector>& positoins);
		AtomVector near(unsigned int atom, Vector position);
};


#endif // ATOM_INDEX_H

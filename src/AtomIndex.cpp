#include "AtomIndex.h"
#include "foreach.h"
#include "math.h"


AtomIndex::AtomIndex(float atomRadius) :
	_atomDiameter(atomRadius * 2.0f)
{}


void AtomIndex::update(const std::vector<Vector>& positions)
{
	_index.clear();

	for (unsigned int i = 0; i < positions.size(); i++)
		_index[toIndex(positions[i].x)].insert(std::pair<int, unsigned int>(toIndex(positions[i].y), i));
}


AtomVector AtomIndex::near(unsigned int atom, Vector position)
{
	AtomVector result;
	int x = toIndex(position.x);
	int y = toIndex(position.y);

	for(Index::iterator xit = _index.lower_bound(x); xit != _index.upper_bound(x+1); xit++)
	{
		for(SubIndex::iterator yit = xit->second.lower_bound(y - 1); yit != xit->second.upper_bound(y + 1); yit++)
		{
			if (yit->second != atom)
				result.push_back(yit->second);
		}
	}

	return result;
}


int AtomIndex::toIndex(float value)
{
	return static_cast<int>(floor(value / _atomDiameter));
}

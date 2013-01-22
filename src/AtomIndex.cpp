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
		_index[positions[i].x].insert(std::pair<float, unsigned int>(positions[i].y, i));
}


AtomVector AtomIndex::near(unsigned int atom, Vector position)
{
	AtomVector result;

	for (Index::iterator xit = _index.lower_bound(position.x);
			xit != _index.upper_bound(position.x + _atomDiameter); xit++)
	{
		for (SubIndex::iterator yit = xit->second.lower_bound(position.y - _atomDiameter);
				yit != xit->second.upper_bound(position.y + _atomDiameter); yit++)
		{
			result.push_back(yit->second);
		}
	}

	return result;
}

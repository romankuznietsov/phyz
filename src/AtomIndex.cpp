#include "AtomIndex.h"
#include "foreach.h"


AtomIndex::AtomIndex(float atomRadius) :
	_collisionDistance(atomRadius * 2.0f)
{
}


void AtomIndex::add(unsigned int atom, Vector position)
{
	_xIndex[position.x].insert(atom);
	_yIndex[position.y].insert(atom);
}


void AtomIndex::update(unsigned int atom, Vector oldPosition, Vector newPosition)
{
	_xIndex[oldPosition.x].erase(atom);
	_yIndex[oldPosition.y].erase(atom);
	_xIndex[newPosition.x].insert(atom);
	_yIndex[newPosition.y].insert(atom);
}


AtomSet AtomIndex::near(unsigned int atom, Vector position)
{
	AtomSet nearX;
	for (auto it = _xIndex.lower_bound(position.x);
			it != _xIndex.upper_bound(position.x + _collisionDistance); it++)
	{
		nearX.insert(it->second.begin(), it->second.end());
	}

	AtomSet nearY;
	for (auto it = _yIndex.lower_bound(position.y - _collisionDistance);
			it != _yIndex.upper_bound(position.y + _collisionDistance); it++)
	{
		nearY.insert(it->second.begin(), it->second.end());
	}

	AtomSet result;
	for (auto it = nearX.begin(); it != nearX.end(); it++)
	{
		if (nearY.find(*it) != nearY.end())
			result.insert(*it);
	}

	result.erase(atom);
	return result;
}

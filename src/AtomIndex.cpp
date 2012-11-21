#include "AtomIndex.h"


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
	return AtomSet();
}

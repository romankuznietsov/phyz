#include "AtomIndex.h"
#include "foreach.h"
#include "math.h"


AtomIndex::AtomIndex(float atomRadius) :
	_step(atomRadius * 2.0f)
{}


void AtomIndex::add(unsigned int atom, Vector position)
{
	_index[toIndex(position.x)][toIndex(position.y)].insert(atom);
}


void AtomIndex::update(unsigned int atom, Vector oldPosition, Vector newPosition)
{
	_index[toIndex(oldPosition.x)][toIndex(oldPosition.y)].erase(atom);
	_index[toIndex(newPosition.x)][toIndex(newPosition.y)].insert(atom);
}


AtomSet AtomIndex::near(unsigned int atom, Vector position)
{
	int x = toIndex(position.x);
	int y = toIndex(position.y);
	AtomSet result;

	result.insert(_index[x][y].begin(), _index[x][y].end());
	result.insert(_index[x][y + 1].begin(), _index[x][y + 1].end());
	result.insert(_index[x][y - 1].begin(), _index[x][y - 1].end());

	x++;
	result.insert(_index[x][y].begin(), _index[x][y].end());
	result.insert(_index[x][y + 1].begin(), _index[x][y + 1].end());
	result.insert(_index[x][y - 1].begin(), _index[x][y - 1].end());

	result.erase(atom);
	return result;
}


int AtomIndex::toIndex(float value)
{
	return static_cast<int>(floor(value / _step));
}

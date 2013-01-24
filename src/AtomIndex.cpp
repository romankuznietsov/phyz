#include "AtomIndex.h"
#include "foreach.h"
#include "math.h"
#include <exception>


const float indexRange = 2000.0f;
const int cellSize = 5;
const int nearCellNumber = 6;


AtomIndex::AtomIndex(float atomRadius) :
	_atomDiameter(atomRadius * 2.0f)
{
	_cellNumber = static_cast<unsigned int>(indexRange / _atomDiameter);
	_indexOffset = _cellNumber / 2;
	_index.reserve(_cellNumber);
	for (unsigned int xi = 0; xi < _cellNumber; xi++)
	{
		_index[xi].reserve(_cellNumber);
		for (unsigned int yi = 0; yi < _cellNumber; yi++)
		{
			_index[xi][yi].reserve(cellSize);
		}
	}
}


void AtomIndex::update(const std::vector<Vector>& positions)
{
	for (unsigned int xi = 0; xi < _cellNumber; xi++)
		for (unsigned int yi = 0; yi < _cellNumber; yi++)
			_index[xi][yi].clear();

	for (unsigned int i = 0; i < positions.size(); i++)
	{
		_index[toIndex(positions[i].x)][toIndex(positions[i].y)].push_back(i);
	}
}


AtomVector AtomIndex::near(unsigned int atom, Vector position)
{
	AtomVector result;
	result.reserve(cellSize * nearCellNumber);
	int x = toIndex(position.x);
	int y = toIndex(position.y);

	for (unsigned int xi = x; xi <= x + 1; xi++)
		for (unsigned int yi = y - 1; yi <= y + 1; yi++)
			foreach(unsigned int atom, _index[xi][yi])
				result.push_back(atom);

	return result;
}


unsigned int AtomIndex::toIndex(float value)
{
	int result = static_cast<int>(floor(value / _atomDiameter)) + _indexOffset;
	if (result < 0 || result >= _cellNumber)
		throw std::exception();
	return result;
}

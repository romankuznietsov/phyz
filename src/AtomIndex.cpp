#include "AtomIndex.h"
#include "foreach.h"
#include "math.h"
#include <exception>
#include <algorithm>


const float indexRange = 4000.0f;
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
		try
		{
			_index[toIndex(positions[i].x)][toIndex(positions[i].y)].push_back(i);
		}
		catch (const std::exception& ex)
		{
			continue;
		}
	}
}


AtomVector AtomIndex::near(unsigned int atom, Vector position)
{
	AtomVector result;
	result.reserve(cellSize * nearCellNumber);
	int x;
	int y;
	try
	{
		x = toIndex(position.x);
		y = toIndex(position.y);
	}
	catch (const std::exception& ex)
	{
		return result;
	}

	for (unsigned int xi = x; xi <= std::min(static_cast<unsigned int>(x + 1), _cellNumber - 1); xi++)
		for (unsigned int yi = std::max(static_cast<unsigned int>(y - 1), 0u);
				yi <= std::min(static_cast<unsigned int>(y + 1), _cellNumber - 1); yi++)
			foreach(unsigned int atom, _index[xi][yi])
				result.push_back(atom);


	return result;
}


unsigned int AtomIndex::toIndex(float value)
{
	int result = static_cast<int>(floor(value / _atomDiameter)) + _indexOffset;
	if (result < 0 || static_cast<unsigned int>(result) >= _cellNumber)
		throw std::exception();
	return result;
}

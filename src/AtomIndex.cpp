#include "AtomIndex.h"
#include "foreach.h"
#include "math.h"
#include <exception>
#include <algorithm>


const float indexRange = 4000.0f;
const int cellSize = 5;
const int nearCellNumber = 6;


AtomIndex::AtomIndex()
{
	_cellNumber = static_cast<unsigned int>(indexRange / Atom::collisionDistance());
	_indexOffset = _cellNumber / 2;
	_index.resize(_cellNumber);
	for (unsigned int xi = 0; xi < _cellNumber; ++xi)
	{
		_index[xi].resize(_cellNumber);
		for (unsigned int yi = 0; yi < _cellNumber; ++yi)
		{
			_index[xi][yi].reserve(cellSize);
		}
	}
}


void AtomIndex::update(const AtomPtrVector& atoms)
{
	for (unsigned int xi = 0; xi < _cellNumber; ++xi)
		for (unsigned int yi = 0; yi < _cellNumber; ++yi)
			_index[xi][yi].clear();

	foreach(AtomPtr atom, atoms)
	{
		try
		{
			_index[toIndex(atom->position().x)][toIndex(atom->position().y)].push_back(atom);
		}
		catch (const std::exception& ex)
		{
			continue;
		}
	}
}


AtomPtrVector AtomIndex::near(const AtomPtr& atom)
{
	AtomPtrVector result;
	result.reserve(cellSize * nearCellNumber);
	int x;
	int y;
	try
	{
		x = toIndex(atom->position().x);
		y = toIndex(atom->position().y);
	}
	catch (const std::exception& ex)
	{
		return result;
	}

	for (unsigned int xi = x; xi <= std::min(static_cast<unsigned int>(x + 1), _cellNumber - 1); ++xi)
		for (unsigned int yi = std::max(static_cast<unsigned int>(y - 1), 0u);
				yi <= std::min(static_cast<unsigned int>(y + 1), _cellNumber - 1); ++yi)
			foreach(AtomPtr atom, _index[xi][yi])
				result.push_back(atom);


	return result;
}


unsigned int AtomIndex::toIndex(float value)
{
	int result = static_cast<int>(floor(value / Atom::collisionDistance())) + _indexOffset;
	if (result < 0 || static_cast<unsigned int>(result) >= _cellNumber)
		throw std::exception();
	return result;
}

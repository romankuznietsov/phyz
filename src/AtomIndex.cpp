#include "AtomIndex.h"
#include "foreach.h"
#include <math.h>


AtomIndex::AtomIndex() :
	_gridSize(Atom::radius() * 2.0f)
{
}


void AtomIndex::add(AtomPtr atom)
{
	int x = static_cast<int>(floor(atom->position().x / _gridSize));
	int y = static_cast<int>(floor(atom->position().y / _gridSize));

	AtomVectorPtr xAtomVector;
	try
	{
		xAtomVector = _xIndex.at(x);
	}
	catch (std::out_of_range)
	{
		xAtomVector.reset(new AtomVector);
		_xIndex[x] = xAtomVector;
	}
	xAtomVector->push_back(atom);

	AtomVectorPtr yAtomVector;
	try
	{
		yAtomVector = _yIndex.at(y);
	}
	catch (std::out_of_range)
	{
		yAtomVector.reset(new AtomVector);
		_yIndex[y] = yAtomVector;
	}
	yAtomVector->push_back(atom);
}


AtomVector AtomIndex::near(AtomPtr atom)
{
	int x = static_cast<int>(floor(atom->position().x / _gridSize));
	int y = static_cast<int>(floor(atom->position().y / _gridSize));
	AtomVector nearX;
	AtomVector nearY;

	for (int i = x - 1; i <= x + 1; i++)
	{
		try
		{
			foreach(AtomPtr atomInIndex, *_xIndex.at(i))
			{
				if (atomInIndex != atom)
				{
					nearX.push_back(atomInIndex);
				}
			}
		}
		catch (std::out_of_range) {}
	}

	for (int i = y - 1; i <= y + 1; i++)
	{
		try
		{
			foreach(AtomPtr atomInIndex, *_yIndex.at(i))
			{
				if (atomInIndex != atom)
				{
					nearY.push_back(atomInIndex);
				}
			}
		}
		catch (std::out_of_range) {}
	}

	AtomVector result;
	foreach(AtomPtr xAtom, nearX)
	{
		foreach(AtomPtr yAtom, nearY)
		{
			if (xAtom == yAtom)
			{
				result.push_back(xAtom);
			}
		}
	}

	return result;
}

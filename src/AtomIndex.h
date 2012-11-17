#include "Atom.h"
#include <unordered_map>
#include <exception>


class AtomIndex
{
	private:
		float _gridSize;
		std::unordered_map<int, AtomVectorPtr> _xIndex;
		std::unordered_map<int, AtomVectorPtr> _yIndex;
	public:
		AtomIndex();
		void add(AtomPtr atom);
		AtomVector near(AtomPtr atom);
};

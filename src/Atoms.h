#ifndef NEW_ATOMS_H
#define NEW_ATOMS_H


#include "Vector.h"
#include <vector>
#include <utility>
#include "AtomIndex.h"


typedef std::pair<unsigned int, unsigned int> Link;


class Atoms
{
	private:
		AtomIndex _index;
		std::vector<Vector> _position;
		std::vector<Vector> _speed;
		std::vector<Link> _links;
		std::vector<float> _linkLength;
		std::vector<bool> _linkDestroyed;

		void updateCollisions();
		void updateLinks();
		void updateAtomPositions();
		void applyForce(unsigned int atom, Vector force);
		unsigned int atomNumber();
		unsigned int linkNumber();

		void drawAtoms();
		void drawLinks();

	public:
		Atoms();
		void draw();
		void update();

		unsigned int add(Vector position, Vector speed);
		void link(unsigned int atom1, unsigned int atom2);
		void addBody(Vector from, Vector to,  Vector speed, float density = 20.0f);
};


#endif // NEW_ATOMS_H

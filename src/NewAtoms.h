#ifndef NEW_ATOMS_H
#define NEW_ATOMS_H


#include "Vector.h"
#include <vector>
#include <utility>


typedef std::pair<unsigned int, unsigned int> NewLink;


class NewAtoms
{
	private:
		std::vector<Vector> _position;
		std::vector<Vector> _speed;
		std::vector<NewLink> _links;

		void updateCollisions();
		void updateLinks();
		void updateAtomPositions();

		void drawAtoms();
		void drawLinks();

	public:
		NewAtoms();
		void draw();
		void update();

		unsigned int add(Vector position, Vector speed);
		void link(unsigned int atom1, unsigned int atom2);
};


#endif // NEW_ATOMS_H

#ifndef NEW_ATOMS_H
#define NEW_ATOMS_H


#include "Vector.h"
#include "Color.h"
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
		std::vector<Color> _color;
		std::vector<Link> _links;
		std::vector<float> _linkLength;
		std::vector<float> _linkForce;
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

		unsigned int add(Vector position, Vector speed, Color color);
		void link(unsigned int atom1, unsigned int atom2, float force);
		void addBody(Vector from, Vector to,  Vector speed, Color color,
				float density = 20.0f, float linkForce = 1000.0f);
};


#endif // NEW_ATOMS_H

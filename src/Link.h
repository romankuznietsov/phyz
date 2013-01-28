#ifndef LINK_H
#define LINK_H


#include "Atom.h"


class Link
{
	private:
		Atom* _atom1;
		Atom* _atom2;
		float _length;
		float _force;
		float _stretch;
		bool _destroyed;

	public:
		Link(Atom* atom1, Atom* atom2, float force, float stretch);
		void update(float dt);
		void draw();
};


#endif // LINK_H

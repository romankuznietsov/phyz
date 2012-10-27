#ifndef ATOM_H
#define ATOM_H


#include "Vector.h"
#include <boost/shared_ptr.hpp>


class Atom
{
	private:
		Vector _position;
		Vector _speed;
		static float _radius;

	public:
		Atom(Vector position = Vector(), Vector speed = Vector());
		void update(float dt);
		void draw();
};


typedef boost::shared_ptr<Atom> AtomPtr;


#endif // ATOM_H

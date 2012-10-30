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
		static float _mass;
		static float _elasticity;

	public:
		Atom(Vector position = Vector(), Vector speed = Vector());
		void update(float dt);
		void draw();

		Vector position();
		Vector speed();
		float radius();
		float mass();
		float elasticity();
		void applyForce(Vector force);
};


typedef boost::shared_ptr<Atom> AtomPtr;


#endif // ATOM_H

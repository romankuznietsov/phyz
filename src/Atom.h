#ifndef ATOM_H
#define ATOM_H


#include "Vector.h"
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>


class Atom
{
	private:
		Vector _position;
		Vector _speed;
		static float _radius;
		static float _mass;
		static float _elasticity;
		boost::mutex _mutex;

	public:
		Atom(Vector position = Vector(), Vector speed = Vector());
		void update(float dt);
		void draw();

		Vector position();
		Vector speed();
		void applyForce(Vector force);
		static float radius();
		static float elasticity();
};


typedef boost::shared_ptr<Atom> AtomPtr;


#endif // ATOM_H

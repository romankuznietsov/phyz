#ifndef ATOM_H
#define ATOM_H


#include "Vector.h"
#include "Color.h"
#include <vector>
#include <boost/thread.hpp>


class Atom
{
    private:
	Vector _position;
	Vector _speed;
	Color _color;
	float _mass;
	boost::mutex _applyForceLock;

	static float _radius;
	static float _elasticity;

    public:
	Atom(Vector position, Vector speed, Color color, float mass);
	void update(float dt);
	void applyForce(Vector force);
	Vector position();
	Vector speed();
	Color color();
	float mass();

	static void setup(float radius, float elasticity);
	static float radius();
	static float elasticity();
	static float collisionDistance();
};


typedef Atom* AtomPtr;
typedef std::vector<AtomPtr> AtomPtrVector;


#endif // ATOM_H

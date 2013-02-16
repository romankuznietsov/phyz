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
	boost::mutex _applyForceLock;

	static float _mass;
	static float _radius;
	static float _elasticity;

    public:
	Atom(Vector position, Vector speed, Color color);
	void update(float dt);
	void draw();
	void applyForce(Vector force);
	Vector position();
	Vector speed();
	Color color();

	static void setup(float radius, float mass, float elasticity);
	static float radius();
	static float mass();
	static float elasticity();
	static float collisionDistance();
};


typedef Atom* AtomPtr;
typedef std::vector<AtomPtr> AtomPtrVector;


#endif // ATOM_H

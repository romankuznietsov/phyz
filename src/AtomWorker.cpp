#include "AtomWorker.h"
#include "foreach.h"


AtomWorker::AtomWorker(AtomIndexPtr index, AtomPtrVector::iterator start, AtomPtrVector::iterator end) :
    _index(index), _start(start), _end(end)
{}


void AtomWorker::operator()(float dt)
{
    for (auto it = _start; it != _end; it++)
    {
	AtomPtr atom = *it;
	AtomPtrVector near = _index->near(atom);
	Vector position1 = atom->position();
	foreach(AtomPtr otherAtom, near)
	{
	    Vector position2 = otherAtom->position();

	    if (position1.x > position2.x || (position1.x == position2.x && position1.y > position2.y))
		continue;

	    if (abs(position1.x - position2.x) >= Atom::collisionDistance() || abs(position1.y - position2.y) >= Atom::collisionDistance())
		continue;

	    float overlap = Atom::collisionDistance() - Vector::distance(position1, position2);

	    if (overlap > 0.0f)
	    {
		Vector force((position1 - position2).normalize() * overlap * overlap *
			Atom::elasticity() * dt);
		atom->applyForce(force);
		otherAtom->applyForce(-force);
	    }
	}
    }
}

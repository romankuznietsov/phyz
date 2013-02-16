#include "Workers.h"
#include "foreach.h"


void Workers::updateAtoms(AtomPtrVector::iterator from, AtomPtrVector::iterator to, float dt)
{
    for (auto it = from; it != to; ++it)
	(*it)->update(dt);
}


void Workers::updateLinks(LinkPtrVector::iterator from, LinkPtrVector::iterator to, float dt)
{
    for (auto it = from; it != to; ++it)
	(*it)->update(dt);
}


void Workers::updateCollisions(AtomIndexPtr index, AtomPtrVector::iterator from, AtomPtrVector::iterator to, float dt)
{
    for (auto it = from; it != to; ++it)
    {
	AtomPtr atom = *it;
	AtomPtrVector near = index->near(atom);
	Vector position1 = atom->position();
	foreach(AtomPtr otherAtom, near)
	{
	    Vector position2 = otherAtom->position();

	    if (position1.x > position2.x || (position1.x == position2.x && position1.y > position2.y))
		continue;

	    if (abs(position1.x - position2.x) >= Atom::collisionDistance()
		    or abs(position1.y - position2.y) >= Atom::collisionDistance())
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

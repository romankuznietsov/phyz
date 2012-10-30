#include "Atoms.h"
#include "foreach.h"


Atoms::Atoms()
{
}


void Atoms::update(float dt)
{
	foreach(AtomPtr atom, *this)
	{
		atom->update(dt);
	}

	for (unsigned int i = 0; i < this->size() - 1; i++)
	{
		for (unsigned int j = i + 1; j < this->size(); j++)
		{
			AtomPtr atom1((*this)[i]);
			AtomPtr atom2((*this)[j]);

			Vector position1 = atom1->position();
			Vector position2 = atom2->position();

			float distance = Vector::distance(position1, position2);
			float collisionDistance = atom1->radius() + atom2->radius();

			if (distance < collisionDistance)
			{
				float force = (collisionDistance - distance) * atom1->elasticity() * atom2->elasticity();

				atom1->applyForce((position1 - position2).normalize() * force * dt);
				atom2->applyForce((position2 - position1).normalize() * force * dt);
			}
		}
	}
}


void Atoms::draw()
{
	foreach(AtomPtr atom, *this)
	{
		atom->draw();
	}
}


void Atoms::add(Vector position, Vector speed)
{
	foreach(AtomPtr atom, *this)
	{
		if (Vector::distance(atom->position(), position) < atom->radius() * 2.0f)
			return;
	}
	this->push_back(AtomPtr(new Atom(position, speed)));
}

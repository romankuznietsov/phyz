#include "Atoms.h"
#include "foreach.h"
#include "GL/freeglut.h"


static float collisionDistance = Atom::radius() * 2.0f;


Atoms::Atoms()
{
}


void Atoms::update(float dt)
{
	foreach(AtomPtr atom, *this)
	{
		atom->update(dt);
	}

	for (unsigned int i = 0; i + 1 < this->size(); i++)
	{
		for (unsigned int j = i + 1; j < this->size(); j++)
		{
			Vector position1 = (*this)[i]->position();
			Vector position2 = (*this)[j]->position();

			// performance improvement
			if (abs(position1.x - position2.x) >= collisionDistance || abs(position1.y - position2.y) >= collisionDistance)
				continue;
			float overlap = collisionDistance - Vector::distance(position1, position2);

			if (overlap > 0.0f)
			{
				Vector force((position1 - position2).normalize() * overlap * overlap * Atom::elasticity() * dt);
				(*this)[i]->applyForce(force);
				(*this)[j]->applyForce(-force);
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

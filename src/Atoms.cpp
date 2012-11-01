#include "Atoms.h"
#include "foreach.h"


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
			AtomPtr atom1((*this)[i]);
			AtomPtr atom2((*this)[j]);

			Vector position1 = atom1->position();
			Vector position2 = atom2->position();

			// performance improvement
			if (abs(position1.x - position2.x) >= collisionDistance || abs(position1.y - position2.y) >= collisionDistance)
				continue;

			float distance = Vector::distance(position1, position2);

			if (distance < collisionDistance)
			{
				float force = (collisionDistance - distance) * Atom::elasticity();

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

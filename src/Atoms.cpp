#include "Atoms.h"
#include "foreach.h"


const float elasticity = 1000.0f;


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
			Vector position1 = atom1->getPosition();
			Vector position2 = atom2->getPosition();
			float distance = Vector::distance(position1, position2);
			float collisionDistance = atom1->radius() + atom2->radius();

			if (distance > collisionDistance)
				continue;

			Vector speed1 = atom1->getSpeed();
			Vector speed2 = atom2->getSpeed();
			float force = (collisionDistance - distance) * elasticity;
			speed1 += (position1 - position2).normalize() * force * dt;
			speed2 += (position2 - position1).normalize() * force * dt;

			atom1->setSpeed(speed1);
			atom2->setSpeed(speed2);
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

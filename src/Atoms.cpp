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
			Vector position1 = atom1->getPosition();
			Vector position2 = atom2->getPosition();

			if (Vector::distance(position1, position2) > atom1->radius() * 2.0f)
				continue;

			Vector speed1 = atom1->getSpeed();
			Vector speed2 = atom2->getSpeed();

			Vector collision = position2 - position1;

			float hit = 0;
			if (speed1.length() != 0.0f)
			{
				float cos = (Vector::scalarMult(speed1, collision)) / (speed1.length() * collision.length());
				hit += speed1.length() * cos;
			}
			if (speed2.length() != 0.0f)
			{
				float cos = (Vector::scalarMult(speed2, -collision)) / (speed2.length() * collision.length());
				hit += speed2.length() * cos;
			}

			if (hit > 0.0f)
			{
				speed1 -= collision.normalize() * hit;
				speed2 += collision.normalize() * hit;

				atom1->setSpeed(speed1);
				atom2->setSpeed(speed2);
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

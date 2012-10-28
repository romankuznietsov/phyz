#include "Atoms.h"
#include "foreach.h"
#include "rangedRandom.h"


Atoms::Atoms()
{
	for (float x = -300.0f; x <= 300.0f; x += 30.0f)
		for (float y = -300.0f; y <= 300.0f; y += 30.0f)
		{
			float speedX = rangedRandom(-100, 100) / 1000.0f;
			float speedY = rangedRandom(-100, 100) / 1000.0f;
			this->push_back(AtomPtr(new Atom(Vector(x, y), Vector(speedX, speedY))));
		}
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

			if (position1.distance(position2) > atom1->radius() * 2.0f)
				continue;

			Vector speed1 = atom1->getSpeed();
			Vector speed2 = atom2->getSpeed();

			Vector collision = position2 - position1;

			float hit = 0;
			if (speed1.length() != 0.0f)
			{
				float cos = (speed1.scalarMult(collision)) / (speed1.length() * collision.length());
				hit += speed1.length() * cos;
			}
			if (speed2.length() != 0.0f)
			{
				float cos = (speed2.scalarMult(-collision)) / (speed2.length() * collision.length());
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

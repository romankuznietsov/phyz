#include "Atoms.h"
#include "foreach.h"
#include "GL/freeglut.h"
#include "debug.h"


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

	int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
	for (unsigned int i = 0; i + 1 < this->size(); i++)
	{
		for (unsigned int j = i + 1; j < this->size(); j++)
		{
			Vector position1 = (*this)[i]->position();
			Vector position2 = (*this)[j]->position();

			// performance improvement
			if (abs(position1.x - position2.x) >= collisionDistance || abs(position1.y - position2.y) >= collisionDistance)
				continue;

			float distance = Vector::distance(position1, position2);

			if (distance < collisionDistance)
			{
				float force = (collisionDistance - distance) * (collisionDistance - distance) * Atom::elasticity();

				(*this)[i]->applyForce((position1 - position2).normalize() * force * dt);
				(*this)[j]->applyForce((position2 - position1).normalize() * force * dt);
			}
		}
	}
	debug("time", glutGet(GLUT_ELAPSED_TIME) - elapsedTime);
}


void Atoms::draw()
{
	foreach(AtomPtr atom, *this)
	{
		atom->draw();
	}
}

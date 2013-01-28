#include "Atoms.h"
#include <GL/freeglut.h>
#include <math.h>
#include <algorithm>
#include "foreach.h"


const float dt = 0.005f;


Atoms::Atoms()
{
}


void Atoms::draw()
{
	foreach(Link* link, _links)
		link->draw();

	foreach(Atom* atom, _atoms)
		atom->draw();
}


void Atoms::update()
{
	updateLinks();
	updateCollisions();
	updateAtomPositions();
}


void Atoms::updateLinks()
{
	foreach(Link* link, _links)
		link->update(dt);
}

void Atoms::updateAtomPositions()
{
	foreach(Atom* atom, _atoms)
		atom->update(dt);
	_index.update(_atoms);
}


void Atoms::updateCollisions()
{
	foreach (AtomPtr atom, _atoms)
	{
		AtomPtrVector near = _index.near(atom);
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


void Atoms::addBody(Vector from, Vector to, Vector speed, Color color,
		float density, float linkForce, float linkStretch)
{
	std::vector<Atom*> body;
	Vector start(std::min(from.x, to.x), std::min(from.y, to.y));
	Vector end(std::max(from.x, to.x), std::max(from.y, to.y));
	float offset = 1.0f;
	for (float x = start.x; x <= end.x; x += density)
	{
		for (float y = start.y; y <= end.y; y += density)
		{
			Atom* atom = new Atom(Vector(x, y + offset * density / 4.0f), speed, color);
			_atoms.push_back(atom);
			body.push_back(atom);
		}
		offset = -offset;
	}

	for (unsigned int i = 0; i < body.size() - 1; i++)
		for (unsigned int j = i + 1; j < body.size(); j++)
		{
			Atom* atom1 = body[i];
			Atom* atom2 = body[j];
			if (Vector::distance(atom1->position(), atom2->position()) <= density * 1.5f)
			{
				_links.push_back(new Link(atom1, atom2, linkForce, linkStretch));
			}
		}
}

#include "AtomList.h"
#include "foreach.h"


AtomList::AtomList()
{
	this->push_back(AtomPtr(new Atom(Vector(0.0f, 0.0f), Vector(0.1f, 0.2f))));
	this->push_back(AtomPtr(new Atom(Vector(0.0f, 0.0f), Vector(-0.3f, -0.1f))));
}


void AtomList::update(float dt)
{
	foreach(AtomPtr atom, *this)
	{
		atom->update(dt);
	}
}


void AtomList::draw()
{
	foreach(AtomPtr atom, *this)
	{
		atom->draw();
	}
}

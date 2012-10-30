#include "Links.h"
#include <GL/freeglut.h>
#include "foreach.h"


void Links::update(float dt)
{
	foreach(LinkPtr link, *this)
	{
		link->update(dt);
	}
}


void Links::draw()
{
	foreach(LinkPtr link, *this)
	{
		link->draw();
	}
}


LinkPtr Links::add(AtomPtr atom1, AtomPtr atom2)
{
	LinkPtr link(new Link(atom1, atom2));
	this->push_back(link);
	return link;
}

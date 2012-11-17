#include "Links.h"
#include <GL/freeglut.h>
#include "foreach.h"


Links::Links() :
	_links(new LinkVector)
{}


void Links::update(float dt)
{
	foreach(LinkPtr link, *_links)
	{
		link->update(dt);
	}
}


void Links::draw()
{
	foreach(LinkPtr link, *_links)
	{
		link->draw();
	}
}


void Links::add(AtomPtr atom1, AtomPtr atom2)
{
	foreach(LinkPtr link, *_links)
	{
		if (link->isBetween(atom1, atom2))
			return;
	}

	_links->push_back(LinkPtr(new Link(atom1, atom2)));
}

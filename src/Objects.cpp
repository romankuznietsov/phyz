#include "Objects.h"
#include <GL/freeglut.h>
#include <math.h>
#include <algorithm>
#include "foreach.h"


const float dt = 0.005f;
const int _maxThreadNumber = 8;


void updateAtoms(AtomPtrVector::iterator from, AtomPtrVector::iterator to, float dt)
{
    for (auto it = from; it != to; it++)
	(*it)->update(dt);
}

void updateLinks(LinkPtrVector::iterator from, LinkPtrVector::iterator to, float dt)
{
    for (auto it = from; it != to; it++)
	(*it)->update(dt);
}

void updateCollisions(AtomIndexPtr index, AtomPtrVector::iterator from, AtomPtrVector::iterator to, float dt)
{
    for (auto it = from; it != to; it++)
    {
	AtomPtr atom = *it;
	AtomPtrVector near = index->near(atom);
	Vector position1 = atom->position();
	foreach(AtomPtr otherAtom, near)
	{
	    Vector position2 = otherAtom->position();

	    if (position1.x > position2.x || (position1.x == position2.x && position1.y > position2.y))
		continue;

	    if (abs(position1.x - position2.x) >= Atom::collisionDistance()
		    or abs(position1.y - position2.y) >= Atom::collisionDistance())
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


Objects::Objects() : _index(new AtomIndex)
{
}


void Objects::draw()
{
    foreach(Link* link, _links)
	link->draw();

    foreach(Atom* atom, _atoms)
	atom->draw();
}


void Objects::update()
{
    updateLinks();
    updateCollisions();
    updateAtomPositions();
}


void Objects::updateLinks()
{
    std::vector<boost::thread*> threads;
    unsigned int linksPerThread = _links.size() / _maxThreadNumber + 1u;
    auto from = _links.begin();
    auto end = _links.end();
    while (from < end)
    {
	auto to = std::min(end, from + linksPerThread);
	threads.push_back(new boost::thread(::updateLinks, from, to, dt));
	from += linksPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
}

void Objects::updateAtomPositions()
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / _maxThreadNumber + 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(::updateAtoms, from, to, dt));
	from += atomsPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
    _index->update(_atoms);
}


void Objects::updateCollisions()
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / _maxThreadNumber + 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(::updateCollisions, _index, from, to, dt));
	from += atomsPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
}


void Objects::addBody(Vector from, Vector to, Vector speed, Color color,
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

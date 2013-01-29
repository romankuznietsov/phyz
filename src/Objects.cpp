#include "Objects.h"
#include <GL/freeglut.h>
#include <math.h>
#include <algorithm>
#include "foreach.h"


const float dt = 0.005f;
const int _maxThreadNumber = 8;


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
    foreach(Link* link, _links)
	link->update(dt);
}

void Objects::updateAtomPositions()
{
    foreach(Atom* atom, _atoms)
	atom->update(dt);
    _index->update(_atoms);
}


void Objects::updateCollisions()
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / _maxThreadNumber;
    if (atomsPerThread == 0u)
	atomsPerThread = 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(AtomWorker(_index, from, to), dt));
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

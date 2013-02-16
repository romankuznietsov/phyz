#include "Objects.h"
#include <GL/freeglut.h>
#include <math.h>
#include <algorithm>
#include "foreach.h"


const int maxThreadNumber = 8;


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


void Objects::update(float dt)
{
    updateLinks(dt);
    updateCollisions(dt);
    updateAtoms(dt);
}


void Objects::updateLinks(float dt)
{
    std::vector<boost::thread*> threads;
    unsigned int linksPerThread = _links.size() / maxThreadNumber + 1u;
    auto from = _links.begin();
    auto end = _links.end();
    while (from < end)
    {
	auto to = std::min(end, from + linksPerThread);
	threads.push_back(new boost::thread(Workers::updateLinks, from, to, dt));
	from += linksPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
}


void Objects::updateAtoms(float dt)
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / maxThreadNumber + 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(Workers::updateAtoms, from, to, dt));
	from += atomsPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
    _index->update(_atoms);
}


void Objects::updateCollisions(float dt)
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / maxThreadNumber + 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(Workers::updateCollisions, _index, from, to, dt));
	from += atomsPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
}


void Objects::addBody(Vector position, Vector size, Vector speed, Color color,
	float density, float linkForce, float linkStretch, float linkDamping)
{
    std::vector<Atom*> body;
    size.x = abs(size.x) / 2.0f;
    size.y = abs(size.y) / 2.0f;
    Vector start = position - size;
    Vector end = position + size;
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

    for (unsigned int i = 0; i < body.size() - 1; ++i)
	for (unsigned int j = i + 1; j < body.size(); ++j)
	{
	    Atom* atom1 = body[i];
	    Atom* atom2 = body[j];
	    if (Vector::distance(atom1->position(), atom2->position()) <= density * 1.5f)
	    {
		_links.push_back(new Link(atom1, atom2, linkForce, linkStretch, linkDamping));
	    }
	}
}


void Objects::writeHeader(std::ofstream& outputFile)
{
    unsigned int numberOfAtoms = _atoms.size();
    float atomRadius = Atom::radius();
    outputFile.write((char*) &numberOfAtoms, sizeof(numberOfAtoms));
    outputFile.write((char*) &atomRadius, sizeof(atomRadius));
    foreach(AtomPtr atom, _atoms)
    {
	Color color = atom->color();
	outputFile.write((char*) &color, sizeof(color));
    }
}


void Objects::writeProgress(std::ofstream& outputFile)
{
    foreach(AtomPtr atom, _atoms)
    {
	Vector position = atom->position();
	outputFile.write((char*) &position, sizeof(position));
    }
}

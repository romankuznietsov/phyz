#include "Model.h"
#include "foreach.h"


const int maxThreadNumber = 8;


Model::Model() : _time(0.0f), _dt(1.0f), _index(new AtomIndex)
{}


void Model::update()
{
    _time += _dt;
    updateLinks();
    updateCollisions();
    updateAtoms();
}


void Model::addBody(Vector position, Vector size,  Vector speed, Color color,
		float density, float mass, float linkForce, float linkStretch,
		float linkDamping)
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
	    Atom* atom = new Atom(Vector(x, y + offset * density / 4.0f),
		    speed, color, mass);
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
	    if (Vector::distance(atom1->position(), atom2->position())
		    <= density * 1.5f)
	    {
		_links.push_back(new Link(atom1, atom2,
			    linkForce, linkStretch, linkDamping));
	    }
	}
}

void Model::updateCollisions()
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / maxThreadNumber + 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(Workers::updateCollisions,
		    _index, from, to, _dt));
	from += atomsPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
}


void Model::updateLinks()
{
    std::vector<boost::thread*> threads;
    unsigned int linksPerThread = _links.size() / maxThreadNumber + 1u;
    auto from = _links.begin();
    auto end = _links.end();
    while (from < end)
    {
	auto to = std::min(end, from + linksPerThread);
	threads.push_back(new boost::thread(Workers::updateLinks,
		    from, to, _dt));
	from += linksPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
}


void Model::updateAtoms()
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / maxThreadNumber + 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(Workers::updateAtoms,
		    from, to, _dt));
	from += atomsPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
    _index->update(_atoms);
}


float Model::time()
{
    return _time;
}


void Model::setDt(float dt)
{
    _dt = dt;
}


DataObjects::Vectors Model::getAtomPositions()
{
    DataObjects::Vectors result;
    foreach (AtomPtr atom, _atoms)
    {
	result.push_back(atom->position());
    }
    return result;
}


DataObjects::VectorPairs Model::getLinkPositions()
{
    DataObjects::VectorPairs result;
    foreach (LinkPtr link, _links)
    {
	if (not link->destroyed())
	result.push_back(link->position());
    }
    return result;
}


DataObjects::Colors Model::getAtomColors()
{
    DataObjects::Colors result;
    foreach (AtomPtr atom, _atoms)
    {
	result.push_back(atom->color());
    }
    return result;
}

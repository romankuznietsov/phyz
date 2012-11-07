#include "Atoms.h"
#include "foreach.h"
#include <GL/freeglut.h>


const int threadNumber = 7;


Atoms::Atoms() :
	_atoms(new AtomVector)
{}


Atoms::~Atoms()
{
	clearThreads();
}


void Atoms::update(float dt)
{
	foreach(AtomPtr atom, *_atoms)
	{
		atom->update(dt);
	}
}


void Atoms::draw()
{
	foreach(AtomPtr atom, *_atoms)
	{
		atom->draw();
	}
}


AtomPtr Atoms::add(Vector position, Vector speed)
{
	AtomPtr atom(new Atom(position, speed));
	_atoms->push_back(atom);
	return atom;
}


void Atoms::refresh()
{
	clearThreads();
	_lists = AtomPairLists(threadNumber);
	int currentThread = 0;
	for (unsigned int i = 0; i + 1 < _atoms->size(); i++)
	{
		for (unsigned int j = i + 1; j < _atoms->size(); j++)
		{
			_lists[currentThread].push_back(AtomPair(i, j));
			currentThread = (currentThread + 1) % threadNumber;
		}
	}
	foreach(AtomPairList pairList, _lists)
	{
		_threads.push_back(new boost::thread(AtomCollisionWorker(_atoms, pairList)));
	}
}


void Atoms::clearThreads()
{
	foreach(boost::thread* thread, _threads)
	{
		thread->interrupt();
		delete thread;
	}
}

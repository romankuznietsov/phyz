#include "Atoms.h"
#include "foreach.h"
#include <GL/freeglut.h>
#include "debug.h"


static float collisionDistance = Atom::radius() * 2.0f;
const int threadNumber = 7;


class AtomCollisionThread
{
	private:
		Atoms* _atoms;
		AtomPairList _list;
		float _dt;

	public:
		AtomCollisionThread(Atoms* atoms, AtomPairList list, float dt) :
			_atoms(atoms), _list(list), _dt(dt)
		{};


		void operator()()
		{
			while(true)
			{
				foreach(AtomPair pair, _list)
				{
					Vector position1 = (*_atoms)[pair.first]->position();
					Vector position2 = (*_atoms)[pair.second]->position();

					// performance improvement
					if (abs(position1.x - position2.x) >= collisionDistance || abs(position1.y - position2.y) >= collisionDistance)
						continue;
					float overlap = collisionDistance - Vector::distance(position1, position2);

					if (overlap > 0.0f)
					{
						Vector force((position1 - position2).normalize() * overlap * overlap * Atom::elasticity() * _dt);
						(*_atoms)[pair.first]->applyForce(force);
						(*_atoms)[pair.second]->applyForce(-force);
					}
				}
				usleep(10);
			}
		};
};



Atoms::Atoms()
{
}


Atoms::~Atoms()
{
	foreach(boost::thread* thread, _threads)
	{
		delete thread;
	}
}


void Atoms::update(float dt)
{
	foreach(AtomPtr atom, *this)
	{
		atom->update(dt);
	}
}


void Atoms::draw()
{
	foreach(AtomPtr atom, *this)
	{
		atom->draw();
	}
}


void Atoms::refresh()
{
	_threads.clear();
	_lists = AtomPairLists(threadNumber);
	int currentThread = 0;
	for (unsigned int i = 0; i + 1 < this->size(); i++)
	{
		for (unsigned int j = i + 1; j < this->size(); j++)
		{
			_lists[currentThread].push_back(AtomPair(i, j));
			currentThread = (currentThread + 1) % threadNumber;
		}
	}
	foreach(AtomPairList pairList, _lists)
	{
		_threads.push_back(new boost::thread(AtomCollisionThread(this, pairList, 0.001f)));
	}
}

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
		PairList _list;
		float _dt;

	public:
		AtomCollisionThread(Atoms* atoms, PairList list, float dt) :
			_atoms(atoms), _list(list), _dt(dt)
		{};


		void operator()()
		{
			foreach(UIPair pair, _list)
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
					(*_atoms)[pair.first]->tsApplyForce(force);
					(*_atoms)[pair.second]->tsApplyForce(-force);
				}
			}
		};
};



Atoms::Atoms()
{
}


void Atoms::update(float dt)
{
	foreach(AtomPtr atom, *this)
	{
		atom->update(dt);
	}

	int elapsed = glutGet(GLUT_ELAPSED_TIME);
	Threads threads;
	foreach(PairList pairList, _lists)
	{
		threads.push_back(new boost::thread(AtomCollisionThread(this, pairList, dt)));
	}
	foreach(boost::thread* thread, threads)
	{
		thread->join();
	}
	debug("time", glutGet(GLUT_ELAPSED_TIME) - elapsed);
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
	_lists = PairLists(threadNumber);
	int currentThread = 0;
	for (unsigned int i = 0; i + 1 < this->size(); i++)
	{
		for (unsigned int j = i + 1; j < this->size(); j++)
		{
			_lists[currentThread].push_back(UIPair(i, j));
			currentThread = (currentThread + 1) % threadNumber;
		}
	}
}

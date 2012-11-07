#include "AtomCollisionWorker.h"
#include "foreach.h"
#include "boost/thread.hpp"


const int updatePeriod = 10;
static float collisionDistance = Atom::radius() * 2.0f;
const float dt = 0.001f;


AtomCollisionWorker::AtomCollisionWorker(AtomVectorPtr atoms, AtomPairList list) :
	_atoms(atoms),
	_list(list)
{}


void AtomCollisionWorker::operator()()
{
	while(true)
	{
		boost::posix_time::ptime startTime = boost::posix_time::second_clock::local_time();
		foreach(AtomPair pair, _list)
		{
			Vector position1 = (*_atoms)[pair.first]->position();
			Vector position2 = (*_atoms)[pair.second]->position();

			if (abs(position1.x - position2.x) >= collisionDistance || abs(position1.y - position2.y) >= collisionDistance)
				continue;
			float overlap = collisionDistance - Vector::distance(position1, position2);

			if (overlap > 0.0f)
			{
				Vector force((position1 - position2).normalize() * overlap * overlap * Atom::elasticity() * dt);
				(*_atoms)[pair.first]->applyForce(force);
				(*_atoms)[pair.second]->applyForce(-force);
			}
		}
		boost::posix_time::ptime endTime = boost::posix_time::second_clock::local_time();
		boost::posix_time::time_duration duration = endTime - startTime;
		if (duration.total_milliseconds() < updatePeriod)
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds(updatePeriod) - duration);
		}
	}
}

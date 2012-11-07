#ifndef ATOMLIST_H
#define ATOMLIST_H


#include <vector>
#include <list>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "Atom.h"
#include "AtomCollisionWorker.h"


typedef std::list<boost::thread*> Threads;


class Atoms
{
	private:
		AtomVectorPtr _atoms;
		AtomPairLists _lists;
		Threads _threads;
		void clearThreads();

	public:
		Atoms();
		~Atoms();
		void update(float dt);
		void draw();
		AtomPtr add(Vector position, Vector speed);
		void refresh();
};


typedef boost::shared_ptr<Atoms> AtomsPtr;


#endif // ATOMLIST_H

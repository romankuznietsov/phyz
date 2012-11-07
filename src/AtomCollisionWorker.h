#ifndef ATOM_COLLISION_WORKER_H
#define ATOM_COLLISION_WORKER_H


#include "Atom.h"


typedef std::pair<unsigned int, unsigned int> AtomPair;
typedef std::list<AtomPair> AtomPairList;
typedef std::vector<AtomPairList> AtomPairLists;


class AtomCollisionWorker
{
	private:
		AtomVectorPtr _atoms;
		AtomPairList _list;

	public:
		AtomCollisionWorker(AtomVectorPtr atoms, AtomPairList list);
		void operator()();
};


#endif // ATOM_COLLISION_WORKER_H

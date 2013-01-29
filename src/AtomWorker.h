#ifndef ATOM_WORKER_H
#define ATOM_WORKER_H


#include "Atom.h"
#include "AtomIndex.h"
#include <boost/thread.hpp>


class AtomWorker
{
    private:
	AtomIndexPtr _index;
	AtomPtrVector::iterator _start;
	AtomPtrVector::iterator _end;
    public:
	AtomWorker(AtomIndexPtr index, AtomPtrVector::iterator start, AtomPtrVector::iterator end);
	void operator()(float dt);
};


#endif // ATOM_WORKER_H

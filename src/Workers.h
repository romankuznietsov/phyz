#ifndef WORKERS_H
#define WORKERS_H


#include "Atom.h"
#include "Link.h"
#include "AtomIndex.h"


namespace Workers
{
    void updateAtoms(AtomPtrVector::iterator from, AtomPtrVector::iterator to, float dt);
    void updateLinks(LinkPtrVector::iterator from, LinkPtrVector::iterator to, float dt);
    void updateCollisions(AtomIndexPtr index, AtomPtrVector::iterator from, AtomPtrVector::iterator to, float dt);
}


#endif // WORKERS_H

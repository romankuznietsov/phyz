#ifndef LINK_WORKER_H
#define LINK_WORKER_H


#include "Link.h"
#include <boost/thread.hpp>


class LinkWorker
{
    private:
	LinkPtrVector::iterator _start;
	LinkPtrVector::iterator _end;
    public:
	LinkWorker(LinkPtrVector::iterator start, LinkPtrVector::iterator end);
	void operator()(float dt);
};


#endif // LINK_WORKER_H

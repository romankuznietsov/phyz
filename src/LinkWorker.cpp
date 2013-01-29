#include "LinkWorker.h"


LinkWorker::LinkWorker(LinkPtrVector::iterator start, LinkPtrVector::iterator end) :
    _start(start), _end(end)
{}


void LinkWorker::operator()(float dt)
{
    for (auto it = _start; it != _end; it++)
	(*it)->update(dt);
}

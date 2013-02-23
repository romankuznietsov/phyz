#include "Buffer.h"


Buffer::Buffer()
{

}


void Buffer::setColors(Colors atomColors)
{
    lock();
    _atomColors = atomColors;
    unlock();
}


void Buffer::setPositions(Vectors atomPositions, VectorPairs links)
{
    lock();
    _atomPositions = atomPositions;
    _links = links;
    unlock();
}


Buffer::Colors Buffer::getAtomColors()
{
    Colors result;
    lock();
    result = _atomColors;
    unlock();
    return result;
}


Buffer::Vectors Buffer::getAtomPositions()
{
    Vectors result;
    lock();
    result = _atomPositions;
    unlock();
    return result;
}


Buffer::VectorPairs Buffer::getLinks()
{
    VectorPairs result;
    lock();
    result = _links;
    unlock();
    return result;
}


void Buffer::lock()
{
    while (!_mutex.try_lock());
}


void Buffer::unlock()
{
    _mutex.unlock();
}

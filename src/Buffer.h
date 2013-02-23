#ifndef BUFFER_H
#define BUFFER_H


#include <boost/thread.hpp>
#include <vector>
#include "Vector.h"
#include "Color.h"


class Buffer
{
    public:
	typedef std::vector<Vector> Vectors;
	typedef std::vector<Color> Colors;
	typedef std::pair<Vector, Vector> VectorPair;
	typedef std::vector<VectorPair> VectorPairs;

	Buffer();
	void setColors(Colors atomColors);
	void setPositions(Vectors atomPositions, VectorPairs links);
	Colors getAtomColors();
	Vectors getAtomPositions();
	VectorPairs getLinks();

    private:
	Vectors _atomPositions;
	Colors _atomColors;
	VectorPairs _links;
	boost::mutex _mutex;
	void lock();
	void unlock();
};


#endif // BUFFER_H

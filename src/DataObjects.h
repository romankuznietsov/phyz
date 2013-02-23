#ifndef DATA_OBJECTS_H
#define DATA_OBJECTS_H


#include <vector>
#include "Vector.h"
#include "Color.h"


namespace DataObjects
{
    typedef std::vector<Vector> Vectors;
    typedef std::vector<Color> Colors;
    typedef std::pair<Vector, Vector> VectorPair;
    typedef std::vector<VectorPair> VectorPairs;
}


#endif // DATA_OBJECTS_H

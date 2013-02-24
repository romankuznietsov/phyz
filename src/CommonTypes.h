#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H


#include <vector>
#include "Vector.h"
#include "Color.h"


namespace CommonTypes
{
    typedef std::vector<Vector> Vectors;
    typedef std::vector<Color> Colors;
    typedef std::pair<Vector, Vector> VectorPair;
    typedef std::vector<VectorPair> VectorPairs;
}


#endif // COMMON_TYPES_H

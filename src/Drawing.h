#ifndef DRAWING_H
#define DRAWING_H


#include "Vector.h"
#include "Color.h"


namespace Drawing
{
    void sphere(Vector position, float radius,
	    Color color = Color(1.0f, 1.0f, 1.0f));

    void line(Vector from, Vector to,
	    Color color = Color(1.0f, 1.0f, 1.0f));
}


#endif // DRAWING_H

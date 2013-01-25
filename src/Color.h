#ifndef COLOR_H
#define COLOR_H


#include <GL/freeglut.h>


struct Color
{
	float r;
	float g;
	float b;
	Color(float red, float green, float blue) :
		r(red), g(green), b(blue)
	{};
	inline void apply(float k = 1.0f)
	{
		glColor3f(r * k, g * k, b * k);
	}
};


#endif // COLOR_H

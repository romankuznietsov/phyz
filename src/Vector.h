#ifndef VECTOR_H
#define VECTOR_H


#include <GL/freeglut.h>
#include <math.h>


class Vector
{
	public:
		float x;
		float y;


		inline Vector() :
			x(0.0f), y(0.0f)
		{};


		inline Vector(float _x, float _y) :
			x(_x), y(_y)
		{};


		inline Vector operator+(Vector other)
		{
			return Vector(x + other.x, y + other.y);
		};


		inline Vector operator-(Vector other)
		{
			return Vector(x - other.x, y - other.y);
		};


		inline Vector operator-()
		{
			return Vector(-x, -y);
		}


		inline Vector operator*(Vector other)
		{
			return Vector(x * other.x, y * other.y);
		};


		inline Vector operator/(Vector other)
		{
			return Vector(x / other.x, y / other.y);
		};


		inline Vector operator*(float number)
		{
			return Vector(x * number, y * number);
		};


		inline Vector operator/(float number)
		{
			return Vector(x / number, y / number);
		};


		inline Vector operator+=(Vector other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}


		inline Vector operator-=(Vector other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}


		inline Vector operator*=(float number)
		{
			x *= number;
			y *= number;
			return *this;
		}


		inline Vector operator/=(float number)
		{
			x /= number;
			y /= number;
			return *this;
		}


		inline void translate()
		{
			glTranslatef(x, y, 0.0f);
		}


		inline void vertex()
		{
			glVertex2f(x, y);
		}


		inline float length()
		{
			return sqrt(x * x + y * y);
		}


		inline float distance(Vector other)
		{
			return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
		}


		inline Vector normalize()
		{
			return *this / length();
		}
};


#endif // VECTOR_H

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


		inline bool operator==(Vector other)
		{
			return x == other.x && y == other.y;
		}


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


		inline Vector normalize()
		{
			return *this / length();
		}

		static inline float scalarMult(Vector v1, Vector v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}


		static inline float distance(Vector v1, Vector v2)
		{
			return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
		}
};


#endif // VECTOR_H

#include "Vector.h"
#include "gtest/gtest.h"


namespace
{
	TEST(VectorTest, Length)
	{
		Vector v(2.0f, 3.0f);
		ASSERT_LT(3.60554f, v.length());
		ASSERT_GT(3.60556f, v.length());
	}


	TEST(VectorTest, Normalize)
	{
		float length = Vector(2.0f, 3.0f).normalize().length();
		ASSERT_LT(0.99f, length);
		ASSERT_GT(1.01, length);
	}


	TEST(VectorTest, ScalarMultiplication)
	{
		Vector v1(2.0f, 3.0f);
		Vector v2(4.0f, 5.0f);
		ASSERT_EQ(Vector::scalarMult(v1, v2), 23.0f);
	}


	TEST(VectorTest, Distance)
	{
		float distance = Vector::distance(Vector(2.0f, 3.0f), Vector(4.0f, 5.0f));
		ASSERT_LT(2.82842f, distance);
		ASSERT_GT(2.82844f, distance);
	}
} // namespace

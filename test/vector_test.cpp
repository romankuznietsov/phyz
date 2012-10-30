#include "Vector.h"
#include "gtest/gtest.h"


namespace
{
	TEST(VectorTest, Constructor)
	{
		Vector v;
		ASSERT_EQ(0.0f, v.x);
		ASSERT_EQ(0.0f, v.y);
	}
} // namespace

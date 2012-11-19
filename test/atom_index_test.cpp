#include "gtest/gtest.h"
#include "AtomIndex.h"
#include <exception>


namespace
{
	TEST(AtomIndex, Near)
	{
		AtomIndex index;

		index.add(0u, Vector(0.0f, 0.0f));
		index.add(1u, Vector(1.0f, 0.0f));
		index.add(2u, Vector(0.0f, 1.0f));
		index.add(3u, Vector(1.0f, 1.0f));

		AtomSet near0 = index.near(0u, Vector(0.0f, 0.0f));
        AtomSet near1 = index.near(1u, Vector(1.0f, 0.0f));
        AtomSet near2 = index.near(2u, Vector(0.0f, 1.0f));
        AtomSet near3 = index.near(3u, Vector(1.0f, 1.0f));

		ASSERT_EQ(3u, near0.size());
		ASSERT_EQ(1u, near1.size());
		ASSERT_EQ(2u, near2.size());
		ASSERT_EQ(0u, near3.size());
	}
}

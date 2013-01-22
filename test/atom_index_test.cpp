#include "gtest/gtest.h"
#include "AtomIndex.h"
#include <exception>


namespace
{
	TEST(AtomIndex, Near)
	{
		AtomIndex index(1.1f);
		std::vector<Vector> positions;

		positions.push_back(Vector(0.0f, 0.0f));
		positions.push_back(Vector(2.0f, 0.0f));
		positions.push_back(Vector(0.0f, 2.0f));
		positions.push_back(Vector(2.0f, 2.0f));
		AtomIndex.update(positions);

		AtomVector near0 = index.near(0u, Vector(0.0f, 0.0f));
        AtomVector near1 = index.near(1u, Vector(2.0f, 0.0f));
        AtomVector near2 = index.near(2u, Vector(0.0f, 2.0f));
        AtomVector near3 = index.near(3u, Vector(2.0f, 2.0f));

		ASSERT_EQ(3u, near0.size());
		ASSERT_EQ(1u, near1.size());
		ASSERT_EQ(3u, near2.size());
		ASSERT_EQ(1u, near3.size());
	}
}

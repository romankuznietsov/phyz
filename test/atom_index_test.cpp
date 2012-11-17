#include "gtest/gtest.h"
#include "AtomIndex.h"
#include "Atom.h"


namespace
{
	TEST(AtomIndex, Near)
	{
		float gridSize = Atom::radius() * 2.0f;
		AtomPtr atom1(new Atom(Vector(1.3f * gridSize, 1.2f * gridSize)));
		AtomPtr atom2(new Atom(Vector(2.2f * gridSize, 1.4f * gridSize)));
		AtomPtr atom3(new Atom(Vector(3.3f * gridSize, 2.8f * gridSize)));
		AtomIndex index;
		index.add(atom1);
		index.add(atom2);
		index.add(atom3);
		ASSERT_EQ(1u, index.near(atom1).size());
		ASSERT_EQ(2u, index.near(atom2).size());
		ASSERT_EQ(1u, index.near(atom3).size());
		ASSERT_EQ(atom2, index.near(atom1)[0]);
		ASSERT_EQ(atom2, index.near(atom3)[0]);
	}
} // namespace

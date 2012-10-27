#ifndef ATOMLIST_H
#define ATOMLIST_H


#include <vector>
#include <boost/shared_ptr.hpp>
#include "Atom.h"


class AtomList : public std::vector<AtomPtr>
{
	public:
		AtomList();
		void update(float dt);
		void draw();
};


typedef boost::shared_ptr<AtomList> AtomListPtr;


#endif // ATOMLIST_H

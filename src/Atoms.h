#ifndef ATOMLIST_H
#define ATOMLIST_H


#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
#include "Atom.h"

class Atoms : public std::vector<AtomPtr>
{
	private:
	public:
		Atoms();
		void update(float dt);
		void draw();
};


typedef boost::shared_ptr<Atoms> AtomsPtr;


#endif // ATOMLIST_H

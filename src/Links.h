#ifndef LINKS_H
#define LINKS_H


#include <vector>
#include <boost/shared_ptr.hpp>
#include "Link.h"


class Links
{
	private:
		LinkVectorPtr _links;
	public:
		Links();
		void update(float dt);
		void draw();
		void add(AtomPtr atom1, AtomPtr atom2);
};


typedef boost::shared_ptr<Links> LinksPtr;


#endif // LINKS_H

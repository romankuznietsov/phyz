#ifndef LINKS_H
#define LINKS_H


#include <vector>
#include <boost/shared_ptr.hpp>
#include "Link.h"


class Links : public std::vector<LinkPtr>
{
	public:
		void update(float dt);
		void draw();
};


typedef boost::shared_ptr<Links> LinksPtr;


#endif // LINKS_H

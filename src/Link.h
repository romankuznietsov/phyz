#ifndef LINK_H
#define LINK_H


#include "Atom.h"
#include <boost/shared_ptr.hpp>
#include <vector>


class Link
{
	private:
		AtomPtr _atom1;
		AtomPtr _atom2;
		float _targetDistance;
		bool _destroyed;
	public:
		Link(AtomPtr atom1, AtomPtr atom2);
		void update(float dt);
		void draw();
		bool isBetween(AtomPtr atom1, AtomPtr atom2);
};


typedef boost::shared_ptr<Link> LinkPtr;
typedef std::vector<LinkPtr> LinkVector;
typedef boost::shared_ptr<LinkVector> LinkVectorPtr;


#endif // LINK_H

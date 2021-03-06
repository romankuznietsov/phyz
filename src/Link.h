#ifndef LINK_H
#define LINK_H


#include "Atom.h"
#include <vector>
#include "CommonTypes.h"


class Link
{
    private:
	Atom* _atom1;
	Atom* _atom2;
	float _length;
	float _force;
	float _stretch;
	float _damping;
	bool _destroyed;

    public:
	Link(Atom* atom1, Atom* atom2, float force, float stretch, float damping);
	void update(float dt);
	bool destroyed();
	CommonTypes::VectorPair position();
};


typedef Link* LinkPtr;
typedef std::vector<LinkPtr> LinkPtrVector;


#endif // LINK_H

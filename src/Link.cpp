#include "Link.h"
#include "Vector.h"
#include "Color.h"


Link::Link(Atom* atom1, Atom* atom2, float force, float stretch, float damping) :
    _atom1(atom1), _atom2(atom2), _length(Vector::distance(_atom1->position(), _atom2->position())),
    _force(force), _stretch(stretch), _damping(damping), _destroyed(false)
{}


void Link::update(float dt)
{
    if (_destroyed) return;

    Vector linkingVector = _atom2->position() - _atom1->position();
    if (linkingVector.length() > _length * _stretch)
    {
	_destroyed = true;
	return;
    }

    Vector targetLinkingVector = linkingVector.normalize() * _length;
    Vector linkDiff = linkingVector - targetLinkingVector;
    float linkDiffLength = linkDiff.length();
    Vector force = linkDiff.normalize() * linkDiffLength * linkDiffLength * dt * _force;
    _atom1->applyForce(force);
    _atom2->applyForce(-force);

    Vector dampingForce = (_atom1->speed() - _atom2->speed()) * _damping * dt;
    _atom1->applyForce(-dampingForce);
    _atom2->applyForce(dampingForce);
}


DataObjects::VectorPair Link::position()
{
    return DataObjects::VectorPair(_atom1->position(), _atom2->position());
}


bool Link::destroyed()
{
    return _destroyed;
}

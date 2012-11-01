#include "Link.h"
#include <GL/freeglut.h>


const float linkForce = 100.0f;
const float damping = 1.0f;
const float maxStretch = 1.5f;


Link::Link(AtomPtr atom1, AtomPtr atom2) :
	_atom1(atom1),
	_atom2(atom2),
	_targetDistance(Vector::distance(_atom1->position(), _atom2->position())),
	_destroyed(false)
{
}


void Link::update(float dt)
{
	if (_destroyed)
		return;

	Vector linkingVector = _atom2->position() - _atom1->position();
	if (linkingVector.length() > _targetDistance * maxStretch)
	{
		_destroyed = true;
		return;
	}

	Vector targetLinkingVector = linkingVector.normalize() * _targetDistance;
	Vector force = linkingVector - targetLinkingVector;
	force *= dt * linkForce;
	_atom1->applyForce(force);
	_atom2->applyForce(-force);

	Vector dampingForce = (_atom1->speed() - _atom2->speed()) * damping * dt;
	_atom1->applyForce(-dampingForce);
	_atom2->applyForce(dampingForce);
}


void Link::draw()
{
	if (_destroyed)
		return;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	_atom1->position().vertex();
	_atom2->position().vertex();
	glEnd();
}


bool Link::isBetween(AtomPtr atom1, AtomPtr atom2)
{
	return ((_atom1 == atom1 && _atom2 == atom2) ||
			(_atom1 == atom2 && _atom2 == atom1));
}

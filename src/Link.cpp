#include "Link.h"
#include <GL/freeglut.h>


Link::Link(AtomPtr atom1, AtomPtr atom2) :
	_atom1(atom1),
	_atom2(atom2),
	_targetDistance(Vector::distance(_atom1->getPosition(), _atom2->getPosition()))
{
}


void Link::update(float dt)
{
	Vector linkingVector = _atom2->getPosition() - _atom1->getPosition();
	Vector targetLinkingVector = linkingVector.normalize() * _targetDistance;
	Vector push1 = linkingVector - targetLinkingVector;
	push1 *= dt;
	Vector push2 = - push1;
	_atom1->setSpeed(_atom1->getSpeed() + push1);
	_atom2->setSpeed(_atom2->getSpeed() + push2);
}


void Link::draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	_atom1->getPosition().vertex();
	_atom2->getPosition().vertex();
	glEnd();
}

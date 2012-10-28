#include "Link.h"
#include <GL/freeglut.h>


const float linkForce = 1000.0f;
const float linkDamping = 1.0f;
const float maxStretch = 1.5f;


Link::Link(AtomPtr atom1, AtomPtr atom2) :
	_atom1(atom1),
	_atom2(atom2),
	_targetDistance(Vector::distance(_atom1->getPosition(), _atom2->getPosition())),
	_destroyed(false)
{
}


void Link::update(float dt)
{
	if (_destroyed)
		return;

	Vector linkingVector = _atom2->getPosition() - _atom1->getPosition();
	if (linkingVector.length() > _targetDistance * maxStretch)
	{
		_destroyed = true;
		return;
	}

	Vector targetLinkingVector = linkingVector.normalize() * _targetDistance;
	Vector push1 = linkingVector - targetLinkingVector;
	push1 *= dt * linkForce;
	Vector push2 = - push1;
	Vector speed1 = _atom1->getSpeed();
	Vector speed2 = _atom2->getSpeed();

	Vector speedDiff = speed1 - speed2;
	speedDiff *= linkDamping * dt;

	speed1 += push1;
	speed2 += push2;
	speed1 -= speedDiff;
	speed2 += speedDiff;

	_atom1->setSpeed(speed1);
	_atom2->setSpeed(speed2);
}


void Link::draw()
{
	if (_destroyed)
		return;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	_atom1->getPosition().vertex();
	_atom2->getPosition().vertex();
	glEnd();
}

#include "Atom.h"
#include "GL/freeglut.h"
#include "math.h"


float Atom::_radius = 20.0f;


Atom::Atom(Vector position, Vector speed) :
	_position(position),
	_speed(speed)
{
}


void Atom::update(float dt)
{
	_position += _speed * dt;
}


void Atom::draw()
{
	glPushMatrix();
	_position.translate();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (float i = 0.0f; i < 2 * M_PI + 0.3; i += 0.3)
	{
		glVertex2f(sin(i) * _radius,
				   cos(i) * _radius);
	}
	glEnd();

	glPopMatrix();
}


Vector Atom::getPosition()
{
	return _position;
}


void Atom::setPosition(Vector position)
{
	_position = position;
}


Vector Atom::getSpeed()
{
	return _speed;
}


void Atom::setSpeed(Vector speed)
{
	_speed = speed;
}


float Atom::radius()
{
	return _radius;
}

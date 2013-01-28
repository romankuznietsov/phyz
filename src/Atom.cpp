#include "Atom.h"
#include <GL/freeglut.h>


const float _radius = 5.0f;
const float _mass = 1.0f;
const float _elasticity = 3000.0f;
const float _collisionDistance = _radius * 2.0f;


Atom::Atom(Vector position, Vector speed, Color color) :
	_position(position), _speed(speed), _color(color)
{}


void Atom::update(float dt)
{
	_position += _speed * dt;
}


void Atom::draw()
{
	glPushMatrix();
	_position.translate();

	glBegin(GL_TRIANGLE_FAN);
	_color.apply();
	glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (float a = 0.0f; a < 2.0f * M_PI + 0.7f; a += 0.7f)
	{
		glVertex2f(sin(a) * _radius,
				cos(a) * _radius);
	}
	glEnd();
	glPopMatrix();
}


void Atom::applyForce(Vector force)
{
	_speed += force / _mass;
}


Vector Atom::position()
{
	return _position;
}


Vector Atom::speed()
{
	return _speed;
}


float Atom::radius()
{
	return _radius;
}


float Atom::mass()
{
	return _mass;
}


float Atom::elasticity()
{
	return _elasticity;
}


float Atom::collisionDistance()
{
	return _collisionDistance;
}

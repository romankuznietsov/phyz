#include "Atom.h"
#include "GL/freeglut.h"
#include "math.h"


float Atom::_radius = 5.0f;
float Atom::_mass = 1.0f;
float Atom::_elasticity = 1500.0f;


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

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (float i = 0.0f; i < 2.0f * M_PI + 0.7f; i += 0.7f)
	{
		glVertex2f(sin(i) * _radius,
				   cos(i) * _radius);
	}
	glEnd();

	//glColor3f(0.0f, 1.0f, 0.0f);
	//glBegin(GL_LINES);
	//glVertex2f(0.0f, 0.0f);
	//_speed.vertex();
	//glEnd();

	glPopMatrix();
}


Vector Atom::position()
{
	return _position;
}


Vector Atom::speed()
{
	return _speed;
}


void Atom::applyForce(Vector force)
{
	while(!_mutex.try_lock()) { }
	_speed += force / _mass;
	_mutex.unlock();
}


float Atom::radius()
{
	return _radius;
}


float Atom::elasticity()
{
	return _elasticity;
}

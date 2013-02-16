#include "Atom.h"
#include "Drawing.h"


float Atom::_radius = 1.0f;
float Atom::_mass = 0.1f;
float Atom::_elasticity = 5000.0f;
auto _sleepTime = boost::posix_time::milliseconds(2);


Atom::Atom(Vector position, Vector speed, Color color) :
    _position(position), _speed(speed), _color(color)
{}


void Atom::setup(float radius, float mass, float elasticity)
{
    _radius = radius;
    _mass = mass;
    _elasticity = elasticity;
}


void Atom::update(float dt)
{
    _position += _speed * dt;
}


void Atom::draw()
{
    Drawing::sphere(_position, _radius, _color);
}


void Atom::applyForce(Vector force)
{
    while(not _applyForceLock.try_lock())
	boost::this_thread::sleep(_sleepTime);

    _speed += force / _mass;
    _applyForceLock.unlock();
}


Vector Atom::position()
{
    return _position;
}


Vector Atom::speed()
{
    return _speed;
}


Color Atom::color()
{
    return _color;
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
    return _radius * 2.0f;
}

#include "Scene.h"
#include <GL/freeglut.h>
#include "foreach.h"


const float sceneSize = 500.0f;


Scene::Scene() :
	_atoms(new Atoms),
	_links(new Links),
	_leftLimit(-sceneSize),
	_rightLimit(sceneSize),
	_topLimit(sceneSize),
	_bottomLimit(-sceneSize)
{
	for (int i = 0; i < 80; i ++)
	{
		_atoms->push_back(AtomPtr(new Atom(Vector((i-40) * 10.0f, 15.0f * (-1 * (i % 2))), Vector())));
	}
	for (int i = 0; i < 80 - 1 ; i ++)
	{
		_links->push_back(LinkPtr(new Link((*_atoms)[i], (*_atoms)[i+1])));
		if ( i < 80 - 2 )
			_links->push_back(LinkPtr(new Link((*_atoms)[i], (*_atoms)[i+2])));
	}
	_atoms->push_back(AtomPtr(new Atom(Vector(0.0f, -470.0f), Vector(0.0f, 500.0f))));
	_atoms->push_back(AtomPtr(new Atom(Vector(-10.0f, -490.0f), Vector(0.0f, 500.0f))));
	_atoms->push_back(AtomPtr(new Atom(Vector(10.0f, -490.0f), Vector(0.0f, 500.0f))));
	_links->push_back(LinkPtr(new Link((*_atoms)[80], (*_atoms)[81])));
	_links->push_back(LinkPtr(new Link((*_atoms)[81], (*_atoms)[82])));
	_links->push_back(LinkPtr(new Link((*_atoms)[82], (*_atoms)[80])));
}


void Scene::update(float dt)
{
	_atoms->update(dt);
	_links->update(dt);
	foreach(AtomPtr atom, *_atoms)
	{
		Vector position = atom->getPosition();
		Vector speed = atom->getSpeed();
		float radius = atom->radius();
		if (position.x + radius >= _rightLimit)
		{
			position.x = _rightLimit - radius;
			speed.x = -speed.x;
		}
		if (position.x - radius <= _leftLimit)
		{
			position.x = _leftLimit + radius;
			speed.x = -speed.x;
		}
		if (position.y + radius >= _topLimit)
		{
			position.y = _topLimit - radius;
			speed.y = -speed.y;
		}
		if (position.y - radius <= _bottomLimit)
		{
			position.y = _bottomLimit + radius;
			speed.y = -speed.y;
		}
		atom->setPosition(position);
		atom->setSpeed(speed);
	}
}


void Scene::draw()
{
	_atoms->draw();
	_links->draw();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(_leftLimit, _topLimit);
	glVertex2f(_rightLimit, _topLimit);
	glVertex2f(_rightLimit, _bottomLimit);
	glVertex2f(_leftLimit, _bottomLimit);
	glEnd();
}

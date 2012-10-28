#include "Scene.h"
#include <GL/freeglut.h>
#include "foreach.h"


const float sceneSize = 500.0f;


Scene::Scene() :
	_leftLimit(-sceneSize),
	_rightLimit(sceneSize),
	_topLimit(sceneSize),
	_bottomLimit(-sceneSize)
{
	_atoms.reset(new Atoms);
}


void Scene::update(float dt)
{
	_atoms->update(dt);
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
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(_leftLimit, _topLimit);
	glVertex2f(_rightLimit, _topLimit);
	glVertex2f(_rightLimit, _bottomLimit);
	glVertex2f(_leftLimit, _bottomLimit);
	glEnd();
}

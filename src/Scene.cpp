#include "Scene.h"
#include <GL/freeglut.h>
#include "foreach.h"
#include "stdio.h"


Scene::Scene() :
	_paused(false),
	_lastDt(0.0f),
	_atoms(new Atoms),
	_links(new Links)
{
	for (int i = 0; i < 80; i ++)
	{
		_atoms->add(Vector(15.0f * (-1 * (i % 2)), (i-40) * 10.0f), Vector());
	}
	for (int i = 0; i < 80 - 1 ; i ++)
	{
		_links->push_back(LinkPtr(new Link((*_atoms)[i], (*_atoms)[i+1])));
		if ( i < 80 - 2 )
			_links->add((*_atoms)[i], (*_atoms)[i+2]);
	}
	_atoms->add(Vector(-820.0f, 10.0f), Vector(500.0f, 0.0f));
	_atoms->add(Vector(-800.0f, -0.0f), Vector(500.0f, 0.0f));
	_atoms->add(Vector(-820.0f, -10.0f), Vector(500.0f, 0.0f));
	_links->add((*_atoms)[80], (*_atoms)[81]);
	_links->add((*_atoms)[81], (*_atoms)[82]);
	_links->add((*_atoms)[82], (*_atoms)[80]);
}


void Scene::update(float dt)
{
	_lastDt = dt;
	if (_paused)
		return;
	_atoms->update(dt);
	_links->update(dt);
}


void Scene::draw(float width, float height)
{
	_atoms->draw();
	_links->draw();
	if (_paused)
	{
		glPushMatrix();
		glTranslatef(- width / 2.0f, -height / 2.0f, 0.0f);
		glScalef(0.2f, 0.2f, 1.0f);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)"Paused");
		glPopMatrix();
	}

	char c[32];
	sprintf(c, "%f", _lastDt);
	glPushMatrix();
	glTranslatef(width / 2.0f - 120.0f, -height / 2.0f, 0.0f);
	glScalef(0.2f, 0.2f, 1.0f);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)c);
	glPopMatrix();
}


void Scene::addAtom(Vector position)
{
	_atoms->add(position, Vector());
}


void Scene::togglePause()
{
	_paused = !_paused;
}

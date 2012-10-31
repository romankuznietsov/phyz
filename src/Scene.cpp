#include "Scene.h"
#include <GL/freeglut.h>
#include "foreach.h"
#include "stdio.h"


Scene::Scene() :
	_paused(true),
	_lastDt(0.0f),
	_atoms(new Atoms),
	_links(new Links)
{
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
	AtomPtr newAtom(new Atom(position));
	foreach(AtomPtr atom, (*_atoms))
	{
		if (Vector::distance(atom->position(), newAtom->position()) < Atom::radius() * 2.0f)
			return;
	}
	_atoms->push_back(newAtom);
}


void Scene::addLink(Vector from, Vector to)
{
}


void Scene::togglePause()
{
	_paused = !_paused;
}

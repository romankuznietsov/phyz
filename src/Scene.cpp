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
	AtomPtr prevAtom1;
	AtomPtr prevAtom2;
	for (int i = 0; i < 40; i ++)
	{
		AtomPtr atom1 = _atoms->add(Vector(10.0f , 20.0f * i - 405.0f), Vector());
		AtomPtr atom2 = _atoms->add(Vector(-10.0f, 20.0f * i - 395.0f), Vector());
		_links->add(atom1, atom2);
		if (prevAtom1 && prevAtom2)
		{
			_links->add(atom1, prevAtom1);
			_links->add(atom2, prevAtom2);
			_links->add(atom1, prevAtom2);
		}
		prevAtom1 = atom1;
		prevAtom2 = atom2;
	}

	AtomPtr atom1 = _atoms->add(Vector(-820.0f, 10.0f), Vector(500.0f, 0.0f));
	AtomPtr atom2 = _atoms->add(Vector(-800.0f, -0.0f), Vector(500.0f, 0.0f));
	AtomPtr atom3 = _atoms->add(Vector(-820.0f, -10.0f), Vector(500.0f, 0.0f));
	_links->add(atom1, atom2);
	_links->add(atom2, atom3);
	_links->add(atom3, atom1);
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

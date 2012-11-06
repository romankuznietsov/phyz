#include "Scene.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <algorithm>
#include "foreach.h"


Scene::Scene() :
	_paused(true),
	_lastDt(0.0f),
	_atoms(new Atoms),
	_links(new Links)
{
	createGrid(Vector(-300.0f, -300.0f), Vector(300.0f, 300.0f), 20.0f, Vector());
	createGrid(Vector(-2000.0f, 20.0f), Vector(-720.0f, -20.0f), 20.0f, Vector(400.0f, 0.0f));
	_atoms->refresh();
}


void Scene::update(float dt)
{
	_lastDt = dt;
	if (_paused)
		return;
	_atoms->update(0.01f);
	_links->update(0.01f);
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


void Scene::createGrid(Vector from, Vector to, float step, Vector speed)
{
	Vector start(std::min(from.x, to.x), std::min(from.y, to.y));
	Vector end(std::max(from.x, to.x), std::max(from.y, to.y));
	Vector offset(0.0f, step/4);
	std::vector<AtomPtr> previousLine;
	std::vector<AtomPtr> currentLine;
	bool toggleLink = true;
	for(Vector current = start; current.x <= end.x; current.x += step)
	{
		AtomPtr previousAtom;
		for(current.y = start.y; current.y <= end.y; current.y += step)
		{
			AtomPtr atom(new Atom(current + offset, speed));
			if (previousAtom)
			{
				_links->add(previousAtom, atom);
			}
			_atoms->push_back(atom);
			previousAtom = atom;
			currentLine.push_back(atom);
		}

		if (!previousLine.empty())
		{
			for (unsigned int i = 0; i < currentLine.size(); i ++)
			{
				_links->add(currentLine[i], previousLine[i]);
				if (toggleLink)
				{
					if (i + 1 < currentLine.size())
						_links->add(currentLine[i], previousLine[i+1]);
				} else {
					if (0 < i)
						_links->add(currentLine[i], previousLine[i-1]);
				}
			}
		}
		previousLine = currentLine;
		currentLine.clear();
		offset = -offset;
		toggleLink = !toggleLink;
	}
}

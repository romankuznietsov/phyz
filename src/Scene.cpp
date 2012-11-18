#include "Scene.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <algorithm>
#include "foreach.h"


Scene::Scene() :
	_paused(true),
	_lastDt(0.0f)
{
	unsigned int atom1 = _newAtoms.add(Vector(-10.0f, 10.0f), Vector());
	unsigned int atom2 = _newAtoms.add(Vector(10.0f, -10.0f), Vector());
	_newAtoms.link(atom1, atom2);
}


void Scene::update(float dt)
{
	_newAtoms.update();
}


void Scene::draw(float width, float height)
{
	_newAtoms.draw();
}


void Scene::addAtom(Vector position)
{
}


void Scene::addLink(Vector from, Vector to)
{
}


void Scene::togglePause()
{
	_paused = !_paused;
}

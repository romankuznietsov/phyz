#include "Scene.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <algorithm>
#include "foreach.h"


Scene::Scene() :
	_paused(true),
	_lastDt(0.0f)
{
	_atoms.addBody(Vector(-200.0f, -200.0f), Vector(200.0f, 200.0f), Vector(), 30.0f);
	_atoms.addBody(Vector(700.0f, 50.0f), Vector(600.0f, -50.0f), Vector(-500.0f, 150.0f), 30.0f);
}


void Scene::update(float dt)
{
	_atoms.update();
}


void Scene::draw(float width, float height)
{
	_atoms.draw();
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

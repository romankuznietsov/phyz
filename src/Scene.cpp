#include "Scene.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <algorithm>
#include "foreach.h"
#include <fstream>


Scene::Scene() :
	_paused(true),
	_lastDt(0.0f)
{
	_atoms.addBody(Vector(-200.0f, -400.0f), Vector(200.0f, 400.0f), Vector(),
			Color(0.7f, 0.2f, 0.2f), 10.0f, 200.0f);
	_atoms.addBody(Vector(900.0f, 0.0f), Vector(600.0f, 100.0f), Vector(-1000.0f, 0.0f),
			Color(0.2f, 0.7f, 0.2f), 10.0f, 1000.0f);
	_atoms.addBody(Vector(-900.0f, -100.0f), Vector(-600.0f, 0.0f), Vector(1000.0f, 0.0f),
			Color(0.2f, 0.2f, 0.7f), 10.0f, 1000.0f);
}


void Scene::update(float dt)
{
	_lastDt = dt;
	_usedTime.push_back(_lastDt);
	_atoms.update();
}


void Scene::draw(float width, float height)
{
	_atoms.draw();
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
}


void Scene::addLink(Vector from, Vector to)
{
}


void Scene::togglePause()
{
	_paused = !_paused;
}

void Scene::writeUsedTime()
{
	std::ofstream file;
	file.open("used_time.csv");
	foreach(float f, _usedTime)
		file << f << std::endl;
	file.close();
}

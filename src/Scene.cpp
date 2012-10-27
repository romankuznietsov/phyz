#include "Scene.h"
#include <GL/freeglut.h>


Scene::Scene() :
	_leftLimit(-400.0f),
	_rightLimit(400.0f),
	_topLimit(400.0f),
	_bottomLimit(-400.0f)
{
	_atoms.reset(new AtomList);
}


void Scene::update(float dt)
{
	_atoms->update(dt);
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

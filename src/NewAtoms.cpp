#include "NewAtoms.h"
#include <GL/freeglut.h>
#include <math.h>
#include "foreach.h"


const float atomRadius = 5.0f;
const float atomMass = 1.0f;
const float atomElasticity = 1500.0f;

const float linkForce = 10.0f;
const float linkDamping = 1.0f;
const float linkStretch = 1.5f;


NewAtoms::NewAtoms()
{
}


void NewAtoms::draw()
{
	drawAtoms();
	drawLinks();
}


void NewAtoms::update()
{
}


unsigned int NewAtoms::add(Vector position, Vector speed)
{
	_position.push_back(position);
	_speed.push_back(speed);
	return _position.size() - 1;
}


void NewAtoms::link(unsigned int atom1, unsigned int atom2)
{
	_links.push_back(NewLink(atom1, atom2));
}


void NewAtoms::drawAtoms()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	for (unsigned int i = 0; i < _position.size(); i++)
	{
		glPushMatrix();
		_position[i].translate();

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0f, 0.0f);
		for (float i = 0.0f; i < 2.0f * M_PI + 0.7f; i += 0.7f)
		{
			glVertex2f(sin(i) * atomRadius,
					cos(i) * atomRadius);
		}
		glEnd();
		glPopMatrix();
	}
}


void NewAtoms::drawLinks()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	foreach(NewLink link, _links)
	{
		_position[link.first].vertex();
		_position[link.second].vertex();
	}
	glEnd();
}


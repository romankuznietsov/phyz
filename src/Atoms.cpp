#include "Atoms.h"
#include <GL/freeglut.h>
#include <math.h>
#include "foreach.h"


const float atomRadius = 5.0f;
const float atomMass = 1.0f;
const float atomElasticity = 1500.0f;
const float collisionDistance = atomRadius * 2.0f;

const float linkForce = 10.0f;
const float linkDamping = 1.0f;
const float linkStretch = 1.5f;

const float dt = 0.001f;


Atoms::Atoms()
{
}


void Atoms::draw()
{
	drawAtoms();
	drawLinks();
}


void Atoms::update()
{
	updateLinks();
	updateCollisions();
	updateAtomPositions();
}


unsigned int Atoms::add(Vector position, Vector speed)
{
	_position.push_back(position);
	_speed.push_back(speed);
	return atomNumber() - 1;
}


void Atoms::link(unsigned int atom1, unsigned int atom2)
{
	_links.push_back(Link(atom1, atom2));
	_linkLength.push_back(Vector::distance(_position[atom1], _position[atom2]));
}


void Atoms::drawAtoms()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	for (unsigned int i = 0; i < atomNumber(); i++)
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


void Atoms::drawLinks()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	foreach(Link link, _links)
	{
		_position[link.first].vertex();
		_position[link.second].vertex();
	}
	glEnd();
}


void Atoms::updateLinks()
{
	for (unsigned int i = 0; i < _links.size(); i++)
	{
		unsigned int atom1 = _links[i].first;
		unsigned int atom2 = _links[i].second;

		Vector linkingVector = _position[atom2] - _position[atom1];
		if (linkingVector.length() > _linkLength[i] * linkStretch)
		{
			// destroy link;
		}

		Vector targetLinkingVector = linkingVector.normalize() * _linkLength[i];
		Vector linkDiff = linkingVector - targetLinkingVector;
		float linkDiffLength = linkDiff.length();
		Vector force = linkDiff.normalize() * linkDiffLength * linkDiffLength * dt * linkForce;
		applyForce(atom1, force);
		applyForce(atom2, -force);

		Vector dampingForce = (_speed[atom1] - _speed[atom2]) * linkDamping * dt;
		applyForce(atom1, -dampingForce);
		applyForce(atom2, dampingForce);
	}
}


void Atoms::updateAtomPositions()
{
	for (unsigned int i = 0; i < atomNumber(); i++)
	{
		_position[i] += _speed[i] * dt;
	}
}


void Atoms::applyForce(unsigned int atom, Vector force)
{
	_speed[atom] += force / atomMass;
}


void Atoms::updateCollisions()
{
	for (unsigned int atom1 = 0; atom1 < atomNumber() - 1; atom1++)
	{
		for (unsigned int atom2 = atom1 + 1; atom2 < atomNumber(); atom2++)
		{
			Vector position1 = _position[atom1];
			Vector position2 = _position[atom2];

			if (abs(position1.x - position2.x) >= collisionDistance || abs(position1.y - position2.y) >= collisionDistance)
				continue;

			float overlap = collisionDistance - Vector::distance(position1, position2);

			if (overlap > 0.0f)
			{
				Vector force((position1 - position2).normalize() * overlap * overlap * atomElasticity * dt);
				applyForce(atom1, force);
				applyForce(atom2, -force);
			}
		}
	}
}


unsigned int Atoms::atomNumber()
{
	_position.size();
}

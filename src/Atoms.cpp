#include "Atoms.h"
#include <GL/freeglut.h>
#include <math.h>
#include <algorithm>
#include "foreach.h"


const float atomRadius = 5.0f;
const float atomMass = 1.0f;
const float atomElasticity = 3000.0f;
const float collisionDistance = atomRadius * 2.0f;

const float linkForce = 1000.0f;
const float linkDamping = 1.0f;
const float linkStretch = 1.5f;

const float dt = 0.001f;


Atoms::Atoms() :
	_index(atomRadius)
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
	unsigned int id = atomNumber() - 1;
	_index.update(_position);
	return id;
}


void Atoms::link(unsigned int atom1, unsigned int atom2)
{
	_links.push_back(Link(atom1, atom2));
	_linkLength.push_back(Vector::distance(_position[atom1], _position[atom2]));
	_linkDestroyed.push_back(false);
}


void Atoms::drawAtoms()
{
	for (unsigned int i = 0; i < atomNumber(); i++)
	{
		glPushMatrix();
		_position[i].translate();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
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
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	for (unsigned int i = 0; i < linkNumber(); i ++)
	{
		if (_linkDestroyed[i])
			continue;
		_position[_links[i].first].vertex();
		_position[_links[i].second].vertex();
	}
	glEnd();
}


void Atoms::updateLinks()
{
	for (unsigned int i = 0; i < linkNumber(); i++)
	{
		if (_linkDestroyed[i])
			continue;
		unsigned int atom1 = _links[i].first;
		unsigned int atom2 = _links[i].second;

		Vector linkingVector = _position[atom2] - _position[atom1];
		if (linkingVector.length() > _linkLength[i] * linkStretch)
			_linkDestroyed[i] = true;

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
		_position[i] += _speed[i] * dt;
	_index.update(_position);
}


void Atoms::applyForce(unsigned int atom, Vector force)
{
	_speed[atom] += force / atomMass;
}


void Atoms::updateCollisions()
{
	for (unsigned int atom = 0; atom < atomNumber(); atom++)
	{
		AtomVector near = _index.near(atom, _position[atom]);
		Vector position1 = _position[atom];
		foreach(unsigned int i, near)
		{
			Vector position2 = _position[i];

			if (position1.x > position2.x || (position1.x == position2.x && position1.y > position2.y))
				continue;

			if (abs(position1.x - position2.x) >= collisionDistance || abs(position1.y - position2.y) >= collisionDistance)
				continue;

			float overlap = collisionDistance - Vector::distance(position1, position2);

			if (overlap > 0.0f)
			{
				Vector force((position1 - position2).normalize() * overlap * overlap * atomElasticity * dt);
				applyForce(atom, force);
				applyForce(i, -force);
			}
		}
	}
}


unsigned int Atoms::atomNumber()
{
	return _position.size();
}


unsigned int Atoms::linkNumber()
{
	return _links.size();
}


void Atoms::addBody(Vector from, Vector to,  Vector speed, float density)
{
	std::vector<unsigned int> body;
	Vector start(std::min(from.x, to.x), std::min(from.y, to.y));
	Vector end(std::max(from.x, to.x), std::max(from.y, to.y));
	float offset = 1.0f;
	for (float x = start.x; x <= end.x; x += density)
	{
		for (float y = start.y; y <= end.y; y += density)
		{
			body.push_back(add(Vector(x, y + offset * density/4.0f), speed));
		}
		offset = -offset;
	}

	for (unsigned int i = 0; i < body.size() - 1; i++)
		for (unsigned int j = i + 1; j < body.size(); j++)
		{
			unsigned int atom1 = body[i];
			unsigned int atom2 = body[j];
			if (Vector::distance(_position[atom1], _position[atom2]) <= density * 1.5f)
			{
				link(atom1, atom2);
			}
		}
}

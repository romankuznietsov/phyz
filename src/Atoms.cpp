#include "Atoms.h"
#include <GL/freeglut.h>
#include <math.h>
#include <algorithm>
#include "foreach.h"


const float atomRadius = 5.0f;
const float atomMass = 1.0f;
const float atomElasticity = 3000.0f;
const float collisionDistance = atomRadius * 2.0f;

const float linkDamping = 10.0f;

const float dt = 0.005f;
const bool fancy = true;


Atoms::Atoms() :
	_index(atomRadius)
{
}


void Atoms::draw()
{
	drawLinks();
	drawAtoms();
}


void Atoms::update()
{
	updateLinks();
	updateCollisions();
	updateAtomPositions();
}


unsigned int Atoms::add(Vector position, Vector speed, Color color)
{
	_position.push_back(position);
	_speed.push_back(speed);
	_color.push_back(color);
	unsigned int id = atomNumber() - 1;
	_index.update(_position);
	return id;
}


void Atoms::link(unsigned int atom1, unsigned int atom2, float force, float stretch)
{
	_links.push_back(Link(atom1, atom2));
	_linkForce.push_back(force);
	_linkStretch.push_back(stretch);
	_linkLength.push_back(Vector::distance(_position[atom1], _position[atom2]));
	_linkDestroyed.push_back(false);
}


void Atoms::drawAtoms()
{
	if (fancy)
	{
		for (unsigned int i = 0; i < atomNumber(); i++)
		{
			glPushMatrix();
			_position[i].translate();

			glBegin(GL_TRIANGLE_FAN);
			_color[i].apply();
			glVertex2f(0.0f, 0.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
			for (float a = 0.0f; a < 2.0f * M_PI + 0.7f; a += 0.7f)
			{
				glVertex2f(sin(a) * atomRadius,
						cos(a) * atomRadius);
			}
			glEnd();
			glPopMatrix();
		}
	} else {
		glPointSize(atomRadius);
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < atomNumber(); i++)
		{
			_color[i].apply();
			_position[i].vertex();
		}
		glEnd();
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
		if (linkingVector.length() > _linkLength[i] * _linkStretch[i])
			_linkDestroyed[i] = true;

		Vector targetLinkingVector = linkingVector.normalize() * _linkLength[i];
		Vector linkDiff = linkingVector - targetLinkingVector;
		float linkDiffLength = linkDiff.length();
		Vector force = linkDiff.normalize() * linkDiffLength * linkDiffLength * dt * _linkForce[i];
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


void Atoms::addBody(Vector from, Vector to, Vector speed, Color color,
		float density, float linkForce, float linkStretch)
{
	std::vector<unsigned int> body;
	Vector start(std::min(from.x, to.x), std::min(from.y, to.y));
	Vector end(std::max(from.x, to.x), std::max(from.y, to.y));
	float offset = 1.0f;
	for (float x = start.x; x <= end.x; x += density)
	{
		for (float y = start.y; y <= end.y; y += density)
		{
			body.push_back(add(Vector(x, y + offset * density/4.0f), speed, color));
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
				link(atom1, atom2, linkForce, linkStretch);
			}
		}
}

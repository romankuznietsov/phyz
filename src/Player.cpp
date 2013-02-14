#include "Player.h"
#include <GL/freeglut.h>
#include "foreach.h"


Player::Player()
{

}


Player::~Player()
{
    if (phyFile.is_open())
	phyFile.close();
}


void Player::loadFile(std::string phyFileName)
{
    phyFile.open(phyFileName.c_str(), std::ios::in | std::ios::binary);
}


bool Player::nextFrame()
{
    _atoms.clear();
    unsigned int numberOfAtoms;
    if (!phyFile.read(reinterpret_cast<char*>(&numberOfAtoms),
	sizeof(numberOfAtoms)))
    {
	return false;
    }
    _atoms.reserve(numberOfAtoms);

    for (unsigned int i = 0u; i < numberOfAtoms; ++i)
    {
	float x;
	float y;
	phyFile.read(reinterpret_cast<char*>(&x), sizeof(x));
	phyFile.read(reinterpret_cast<char*>(&y), sizeof(y));
	_atoms.push_back(Vector(x, y));
    }
    return true;
}


void Player::display(int windowWidth, int windowHeight)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(5.0f);
    glPushMatrix();
    glTranslatef(windowWidth / 2.0f, windowHeight / 2.0f, 0.0f);
    glScalef(1.0f, -1.0f, 1.0f);

    glBegin(GL_POINTS);
    foreach(Vector& atom, _atoms)
    {
	atom.vertex();
    }
    glEnd();

    glPopMatrix();
}

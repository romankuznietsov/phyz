#include "Player.h"
#include "Atom.h"
#include <GL/freeglut.h>


Player::Player()
{

}


Player::~Player()
{
    if (_phyFile.is_open())
	_phyFile.close();
}


bool Player::loadFile(std::string phyFileName)
{
    _phyFile.open(phyFileName.c_str(), std::ios::in | std::ios::binary);
    return readHeader();
}


bool Player::readHeader()
{
   if (!_phyFile.read(reinterpret_cast<char*>(&_numberOfAtoms),
	   sizeof(_numberOfAtoms)))
       return false;
   _atoms.reserve(_numberOfAtoms);
   _colors.reserve(_numberOfAtoms);

   for (unsigned int i = 0u; i < _numberOfAtoms; ++i)
   {
       Color color;
       if(!_phyFile.read(reinterpret_cast<char*>(&color), sizeof(color)))
	   return false;
       _colors.push_back(color);
   }
   return true;
}


bool Player::nextFrame()
{
    _atoms.clear();

    for (unsigned int i = 0u; i < _numberOfAtoms; ++i)
    {
	Vector position;
	if (!_phyFile.read(
		    reinterpret_cast<char*>(&position), sizeof(position)))
	    return false;
	_atoms.push_back(position);
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

    glPointSize(Atom::radius() * 3.0f);
    glBegin(GL_POINTS);
    for (unsigned int i = 0u; i < _numberOfAtoms; ++i)
    {
	_colors[i].apply();
	_atoms[i].vertex();
    }
    glEnd();

    glPopMatrix();
}

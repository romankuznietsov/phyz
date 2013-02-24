#include "PhyLoader.h"
#include "Atom.h"


PhyLoader::PhyLoader()
{

}


PhyLoader::~PhyLoader()
{
    if (_inputFile.is_open())
	_inputFile.close();
}


bool PhyLoader::load(std::string fileName)
{
    _inputFile.open(fileName.c_str(), std::ios::in | std::ios::binary);
    return readHeader();
}


bool PhyLoader::readHeader()
{
   if (!_inputFile.read(reinterpret_cast<char*>(&_numberOfAtoms),
	   sizeof(_numberOfAtoms)))
       return false;

   float atomRadius;
   if (!_inputFile.read(reinterpret_cast<char*>(&atomRadius),
	   sizeof(atomRadius)))
       return false;
   Atom::setup(atomRadius, 0.0f);

   _atoms.reserve(_numberOfAtoms);
   _colors.reserve(_numberOfAtoms);

   for (unsigned int i = 0u; i < _numberOfAtoms; ++i)
   {
       Color color;
       if(!_inputFile.read(reinterpret_cast<char*>(&color), sizeof(color)))
	   return false;
       _colors.push_back(color);
   }
   return true;
}


bool PhyLoader::nextFrame()
{
    _atoms.clear();

    for (unsigned int i = 0u; i < _numberOfAtoms; ++i)
    {
	Vector position;
	if (!_inputFile.read(
		    reinterpret_cast<char*>(&position), sizeof(position)))
	    return false;
	_atoms.push_back(position);
    }
    return true;
}


CommonTypes::Vectors PhyLoader::getAtomPositions()
{
    return _atoms;
}


CommonTypes::Colors PhyLoader::getAtomColors()
{
    return _colors;
}

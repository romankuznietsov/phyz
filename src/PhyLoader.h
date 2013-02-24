#ifndef PHY_LOADER_H
#define PHY_LOADER_H


#include <string>
#include <fstream>
#include "CommonTypes.h"


class PhyLoader
{
    public:
	PhyLoader();
	~PhyLoader();
	bool load(std::string fileName);
	bool nextFrame();
	CommonTypes::Vectors getAtomPositions();
	CommonTypes::Colors getAtomColors();

    private:
	std::ifstream _inputFile;
	unsigned int _numberOfAtoms;
	CommonTypes::Vectors _atoms;
	CommonTypes::Colors _colors;
	bool readHeader();
};


#endif // PHY_LOADER_H

#ifndef PHY_LOADER_H
#define PHY_LOADER_H


#include <string>
#include <fstream>
#include "DataObjects.h"


class PhyLoader
{
    public:
	PhyLoader();
	~PhyLoader();
	bool load(std::string fileName);
	bool nextFrame();
	DataObjects::Vectors getAtomPositions();
	DataObjects::Colors getAtomColors();

    private:
	std::ifstream _inputFile;
	unsigned int _numberOfAtoms;
	DataObjects::Vectors _atoms;
	DataObjects::Colors _colors;
	bool readHeader();
};


#endif // PHY_LOADER_H

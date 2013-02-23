#ifndef PHY_WRITER_H
#define PHY_WRITER_H


#include "DataObjects.h"
#include <fstream>
#include <string>


class PhyWriter
{
    public:
	PhyWriter();
	~PhyWriter();
	void setOutput(std::string fileName);
	void writeHeader(DataObjects::Colors atomColors);
	void writeProgress(DataObjects::Vectors atomPositions);

    private:
	std::ofstream _outputFile;
};


#endif // PHY_WRITER_H

#ifndef PHY_WRITER_H
#define PHY_WRITER_H


#include "CommonTypes.h"
#include <fstream>
#include <string>


class PhyWriter
{
    public:
	PhyWriter();
	~PhyWriter();
	void setOutput(std::string fileName);
	void writeHeader(CommonTypes::Colors atomColors);
	void writeProgress(CommonTypes::Vectors atomPositions);

    private:
	std::ofstream _outputFile;
};


#endif // PHY_WRITER_H

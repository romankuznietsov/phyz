#include "PhyWriter.h"
#include "Atom.h"
#include "foreach.h"


PhyWriter::PhyWriter()
{

}


PhyWriter::~PhyWriter()
{
    if (_outputFile.is_open())
	_outputFile.close();
}


void PhyWriter::setOutput(std::string fileName)
{
    if (_outputFile.is_open())
	_outputFile.close();

    _outputFile.open(fileName.c_str(), std::ios::out | std::ios::binary);
}


void PhyWriter::writeHeader(DataObjects::Colors atomColors)
{

    if (!_outputFile.is_open())
	return;

    unsigned int numberOfAtoms = atomColors.size();
    float atomRadius = Atom::radius();
    _outputFile.write((char*) &numberOfAtoms, sizeof(numberOfAtoms));
    _outputFile.write((char*) &atomRadius, sizeof(atomRadius));
    foreach(Color color, atomColors)
    {
	_outputFile.write((char*) &color, sizeof(color));
    }
}


void PhyWriter::writeProgress(DataObjects::Vectors atomPositions)
{
    if (!_outputFile.is_open())
	return;

    foreach(Vector atomPosition, atomPositions)
    {
	_outputFile.write((char*) &atomPosition, sizeof(atomPosition));
    }

}

#ifndef YAML_PHY_MODE_H
#define YAML_PHY_MODE_H


#include "burden/Burden.h"
#include "Model.h"
#include "PhyWriter.h"
#include <string>


class YamlPhyMode
{
    public:
	YamlPhyMode();
	void loadFile(std::string inputFileName);
	void calculate(std::string outputFileName, float duration,
		float recordDt);

    private:
	Model _model;
	PhyWriter _writer;
};


#endif // YAML_PHY_MODE_H

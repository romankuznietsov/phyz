#ifndef YAML_PHY_MODE_H
#define YAML_PHY_MODE_H


#include "gxy/Burden.h"
#include "Model.h"
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
};


#endif // YAML_PHY_MODE_H

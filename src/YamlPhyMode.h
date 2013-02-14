#ifndef YAML_PHY_MODE_H
#define YAML_PHY_MODE_H


#include "gxy/Gxy.h"
#include "Model.h"
#include <string>


class YamlPhyMode
{
    public:
	YamlPhyMode();
	void loadFile(std::string yamlFileName);
	void calculate(std::string phyFileName, float duration, float dt,
		float recordDt);

    private:
	Model _model;
};


#endif // YAML_PHY_MODE_H

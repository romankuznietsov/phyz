#include "YamlPhyMode.h"
#include <fstream>
#include <iostream>


YamlPhyMode::YamlPhyMode()
{

}


void YamlPhyMode::loadFile(std::string yamlFileName)
{
    _model.loadFile(yamlFileName);
}


void YamlPhyMode::calculate(std::string phyFileName, float duration, float dt)
{
    std::ofstream outputFile(phyFileName.c_str(),
        std::ios::out | std::ios::binary);

    float lastOutput = 0.0f;
    for (float time = 0.0f; time <= duration; time += dt)
    {
        _model.update(dt);
        _model.writeProgress(outputFile);
	if (time - lastOutput >= 1.0f)
	{
	    std::cout << time << " / " << duration << std::endl;
	    lastOutput = time;
	}
    }

    outputFile.close();
}

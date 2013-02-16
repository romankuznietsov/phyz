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


void YamlPhyMode::calculate(std::string phyFileName,
	float duration, float recordDt)
{
    std::ofstream outputFile(phyFileName.c_str(),
        std::ios::out | std::ios::binary);

    float previousRecordTime = 0.0f;
    _model.writeHeader(outputFile);
    _model.writeProgress(outputFile);
    for (float time = 0.0f; time <= duration; time += _model.dt())
    {
	if (time - previousRecordTime >= recordDt)
	{
	    _model.writeProgress(outputFile);
	    previousRecordTime = time;
	    std::cout << time << " / " << duration << std::endl;
	}

        _model.update();
    }

    outputFile.close();
}

#include "YamlPhyMode.h"
#include <fstream>


YamlPhyMode::YamlPhyMode()
{

}


void YamlPhyMode::loadFile(std::string yamlFileName)
{
    _model.loadFile(yamlFileName);
}


void YamlPhyMode::calculate(std::string phyFileName, float duration,
	float dt, float recordDt)
{
    std::ofstream outputFile(phyFileName.c_str(),
        std::ios::out | std::ios::binary);

    float previousRecordTime = 0.0f;
    _model.writeProgress(outputFile);
    for (float time = 0.0f; time <= duration; time += dt)
    {
	if (time - previousRecordTime >= recordDt)
	{
	    _model.writeProgress(outputFile);
	    previousRecordTime = time;
	}

        _model.update(dt);
    }

    outputFile.close();
}

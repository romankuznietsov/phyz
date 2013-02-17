#include "YamlPhyMode.h"
#include <fstream>
#include <iostream>


YamlPhyMode::YamlPhyMode()
{

}


void YamlPhyMode::loadFile(std::string inputFileName)
{
    _model.loadFile(inputFileName);
}


void YamlPhyMode::calculate(std::string outputFileName,
	float duration, float recordDt)
{
    _model.setOutputFile(outputFileName);

    float previousRecordTime = 0.0f;
    _model.writeHeader();
    _model.writeProgress();
    while (_model.time() <= duration)
    {
	if (_model.time() - previousRecordTime >= recordDt)
	{
	    _model.writeProgress();
	    previousRecordTime = _model.time();
	    std::cout << _model.time() << " / " << duration << std::endl;
	}

        _model.update();
    }
}

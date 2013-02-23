#include "YamlPhyMode.h"
#include <fstream>
#include <iostream>
#include "YamlLoader.h"


YamlPhyMode::YamlPhyMode()
{

}


void YamlPhyMode::loadFile(std::string inputFileName)
{
    YamlLoader().load(inputFileName, _model);
}


void YamlPhyMode::calculate(std::string outputFileName,
	float duration, float recordDt)
{
    _writer.setOutput(outputFileName);

    float previousRecordTime = 0.0f;
    _writer.writeHeader(_model.getAtomColors());
    _writer.writeProgress(_model.getAtomPositions());
    while (_model.time() <= duration)
    {
	if (_model.time() - previousRecordTime >= recordDt)
	{
	    _writer.writeProgress(_model.getAtomPositions());
	    previousRecordTime = _model.time();
	    std::cout << _model.time() << " / " << duration << std::endl;
	}

        _model.update();
    }
}

#include "YamlGLMode.h"
#include "YamlPhyMode.h"
#include "PhyGLMode.h"
#include <boost/program_options.hpp>
#include <string>
#include <iostream>


int main(int argc, char** argv)
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
	("mode,m", boost::program_options::value<std::string>()->default_value("yaml-gl"), "mode (yaml-gl, yaml-phy, phy-gl)")
	("output-file,o", boost::program_options::value<std::string>()->default_value("output.phy"), "output file")
	("input-file,i", boost::program_options::value<std::string>(), "input file")
	("duration,d", boost::program_options::value<float>()->default_value(10.0f), "duation to calculate")
	("record-step,r", boost::program_options::value<float>()->default_value(0.01f), "record time step")
	;
    boost::program_options::positional_options_description pos;
    pos.add("input-file", -1);
    boost::program_options::variables_map consoleArguments;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(pos).run(), consoleArguments);
    boost::program_options::notify(consoleArguments);

    if (!consoleArguments.count("input-file"))
    {
	std::cout << "No input file." << std::endl;
	return 1;
    }

    std::string mode = consoleArguments["mode"].as<std::string>();
    std::string inputFile = consoleArguments["input-file"].as<std::string>();
    std::string outputFile = consoleArguments["output-file"].as<std::string>();
    float duration = consoleArguments["duration"].as<float>();
    float recordStep = consoleArguments["record-step"].as<float>();

    if (mode == "yaml-gl")
    {
	YamlGLMode mode;
	mode.loadFile(inputFile);
	mode.run();
    }

    if (mode == "yaml-phy")
    {

	std::cout << "recording to " << outputFile << std::endl;
	std::cout << "duration: " << duration << std::endl;
	std::cout << "record step: " << recordStep << std::endl;
	std::cout << "working..." << std::endl;

	YamlPhyMode mode;
	mode.loadFile(inputFile);
	mode.calculate(outputFile, duration, recordStep);
    }

    if (mode == "phy-gl")
    {
	PhyGLMode mode;
	mode.loadFile(inputFile);
	mode.run();
    }

    return 0;
}

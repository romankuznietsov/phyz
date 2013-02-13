#include "YamlGLMode.h"
#include "YamlPhyMode.h"
#include <boost/program_options.hpp>
#include <string>
#include <iostream>


int main(int argc, char** argv)
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
	("mode,m", boost::program_options::value<std::string>()->default_value("yaml-gl"), "mode (yaml-gl, yaml-phy, phy-gl)")
	("output-file,o", boost::program_options::value<std::string>(), "output file")
	("input-file,i", boost::program_options::value<std::string>(), "input file")
	;
    boost::program_options::positional_options_description pos;
    pos.add("input-file", -1);
    boost::program_options::variables_map consoleArguments;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(pos).run(), consoleArguments);
    boost::program_options::notify(consoleArguments);

    std::string mode = consoleArguments["mode"].as<std::string>();

    if (!consoleArguments.count("input-file"))
    {
	std::cout << "No input file." << std::endl;
	return 1;
    }
    std::string inputFile = consoleArguments["input-file"].as<std::string>();

    if (mode == "yaml-gl")
    {
        YamlGLMode mode;
        mode.loadFile(inputFile);
        mode.run();
    }

    if (mode == "yaml-phy")
    {
	if (!consoleArguments.count("output-file"))
	{
	    std::cout << "No output file." << std::endl;
	    return 1;
	}
	std::string outputFile = consoleArguments["output-file"].as<std::string>();

	YamlPhyMode mode;
	mode.loadFile(inputFile);
	mode.calculate(outputFile, 1000.0f, 0.005f);
    }


    return 0;
}

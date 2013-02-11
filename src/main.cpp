#include "Application.h"
#include <boost/program_options.hpp>
#include <string>
#include <iostream>


int main(int argc, char** argv)
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
	("input-file,i", boost::program_options::value<std::string>(), "input file")
	("output-file,o", boost::program_options::value<std::string>(), "output file")
	("input-type,t", boost::program_options::value<std::string>()->default_value("yml"), "input file type (yml or phy)")
	("duration,d", boost::program_options::value<float>(), "duration to render")
	("step,s", boost::program_options::value<float>(), "update time step")
	;
    boost::program_options::positional_options_description pos;
    pos.add("input-file", -1);
    boost::program_options::variables_map consoleArguments;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(pos).run(), consoleArguments);
    boost::program_options::notify(consoleArguments);

    std::string inputFile = consoleArguments["input-file"].as<std::string>();
    std::string fileType = consoleArguments["input-type"].as<std::string>();

    if (!consoleArguments.count("input-file"))
	return 1;

    if (fileType != "yml" && fileType != "phy")
	return 1;

    if (consoleArguments.count("output-file") && !(consoleArguments.count("duration") && consoleArguments.count("step")))
	return 1;

    if (fileType == "yml")
    {
	if (consoleArguments.count("output-file"))
	{
	    std::string outputFile = consoleArguments["output-file"].as<std::string>();
	    ScenePtr scene = new Scene(inputFile, outputFile);
	    scene->update(0.001f);
	    scene->writeProgress();
	    delete scene;
	}
	else
	{
	    Application(new Scene(inputFile)).run();
	}

    }

    return 0;
}

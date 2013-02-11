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
	("input-type,t", boost::program_options::value<std::string>()->default_value("yml"), "input file type (yml or phy)");
    boost::program_options::positional_options_description pos;
    pos.add("input-file", -1);
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);
    boost::program_options::notify(vm);

    if (!vm.count("input-file"))
	return 1;

    std::string inputFile = vm["input-file"].as<std::string>();

    std::string fileType = vm["input-type"].as<std::string>();
    if (fileType != "yml" && fileType != "phy")
	return 1;

    if (fileType == "yml")
    {
	ScenePtr scene = new Scene(inputFile);
	Application(scene).run();
    }

    return 0;
}

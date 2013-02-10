#include "Application.h"
#include <boost/program_options.hpp>
#include <string>


int main(int argc, char** argv)
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
	("scene-file,S", boost::program_options::value<std::string>(), "yaml file containing scene info")
	("render-file,R", boost::program_options::value<std::string>(), "file containing rendered scene")
	("no-gl,G", "render to file");
    Application app(argc, argv);
    app.run();
}

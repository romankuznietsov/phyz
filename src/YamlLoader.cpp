#include "YamlLoader.h"
#include "Vector.h"
#include "Color.h"
#include "Atom.h"
#include <fstream>
#include <yaml-cpp/yaml.h>


YamlLoader::YamlLoader()
{

}


bool YamlLoader::load(std::string fileName, Model& model)
{
    std::ifstream file(fileName.c_str());

    try
    {
	YAML::Parser parser(file);
	YAML::Node doc;
	parser.GetNextDocument(doc);

	float dt;
	doc["dt"] >> dt;
	model.setDt(dt);

	const YAML::Node& atomNode = doc["atom"];

	float atomRadius;
	float atomElasticity;

	atomNode["radius"] >> atomRadius;
	atomNode["elasticity"] >> atomElasticity;

	Atom::setup(atomRadius, atomElasticity);

	const YAML::Node& bodiesNode = doc["bodies"];
	for (YAML::Iterator it = bodiesNode.begin();
		it != bodiesNode.end(); ++it)
	{
	    const YAML::Node& positionNode = (*it)["position"];
	    Vector position;
	    positionNode["x"] >> position.x;
	    positionNode["y"] >> position.y;

	    const YAML::Node& sizeNode = (*it)["size"];
	    Vector size;
	    sizeNode["x"] >> size.x;
	    sizeNode["y"] >> size.y;

	    const YAML::Node& speedNode = (*it)["speed"];
	    Vector speed;
	    speedNode["x"] >> speed.x;
	    speedNode["y"] >> speed.y;

	    const YAML::Node& colorNode = (*it)["color"];
	    Color color;
	    colorNode["r"] >> color.r;
	    colorNode["g"] >> color.g;
	    colorNode["b"] >> color.b;

	    float density;
	    (*it)["density"] >> density;
	    float linkForce;
	    (*it)["link_force"] >> linkForce;
	    float linkStretch;
	    (*it)["link_stretch"] >> linkStretch;
	    float linkDamping;
	    (*it)["link_damping"] >> linkDamping;
	    float mass;
	    (*it)["mass"] >> mass;

	    model.addBody(position, size, speed, color, density, mass,
		    linkForce, linkStretch, linkDamping);
	}
    }
    catch (YAML::Exception& e)
    {
	return false;
    }
    return true;
}

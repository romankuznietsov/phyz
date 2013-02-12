#include "Model.h"
#include "foreach.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <GL/freeglut.h>
#include <yaml-cpp/yaml.h>


Model::Model() : _paused(true), _lastDt(0.0f)
{}


void Model::update(float dt)
{
    _lastDt = dt;
    if (!_paused)
	_objects.update();
}


void Model::draw(float width, float height)
{
    glPushMatrix();
    glTranslatef(width / 2.0f, height / 2.0f, 0.0f);
    glScalef(1.0f, -1.0f, 1.0f);
    _objects.draw();
    glPopMatrix();

    char c[32];
    if (_paused)
	sprintf(c, "PAUSED");
    else
	sprintf(c, "%f", _lastDt);

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(width - 120.0f, height -  10.0f, 0.0f);
    glScalef(0.2f, -0.2f, 1.0f);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)c);
    glPopMatrix();

}


void Model::writeProgress(std::ofstream outputFile)
{
    _objects.writeAtomPositions(outputFile);
}


void Model::togglePause()
{
    _paused = !_paused;
}


void Model::loadFile(std::string yamlFileName)
{
    std::ifstream file(yamlFileName.c_str());

    try
    {
	YAML::Parser parser(file);
	YAML::Node doc;
	parser.GetNextDocument(doc);

	for (YAML::Iterator it = doc.begin(); it != doc.end(); ++it)
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

	    _objects.addBody(position, size, speed, color, density,
		    linkForce, linkStretch, linkDamping);
	}
    }
    catch (YAML::Exception& e)
    {
	std::cout << "Bad model file format" << std::endl;
	std::cout << e.what() << std::endl;
    }
}

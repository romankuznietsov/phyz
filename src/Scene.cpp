#include "Scene.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <algorithm>
#include "foreach.h"
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <iostream>


Scene::Scene() :
    _paused(true),
    _lastDt(0.0f)
{}


void Scene::update(float dt)
{
    _lastDt = dt;
    _usedTime.push_back(_lastDt);
    if (!_paused)
	_objects.update();
}


void Scene::draw(float width, float height)
{
    _objects.draw();
    glColor3f(1.0f, 1.0f, 1.0f);
    char c[32];
    if (_paused)
	sprintf(c, "PAUSED");
    else
	sprintf(c, "%f", _lastDt);
    glPushMatrix();
    glTranslatef(width / 2.0f - 120.0f, -height / 2.0f + 10.0f, 0.0f);
    glScalef(0.2f, 0.2f, 1.0f);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)c);
    glPopMatrix();

}


void Scene::addAtom(Vector position)
{
}


void Scene::addLink(Vector from, Vector to)
{
}


void Scene::togglePause()
{
    _paused = !_paused;
}

void Scene::writeUsedTime()
{
    std::ofstream file;
    file.open("used_time.csv");
    foreach(float f, _usedTime)
	file << f << std::endl;
    file.close();
}


void Scene::load(int argc, char** argv)
{
    if (argc != 2)
	return;
    std::ifstream file(argv[1]);

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

	    _objects.addBody(position, size, speed, color, density, linkForce, linkStretch, linkDamping);
	}
    }
    catch (YAML::Exception& e)
    {
	std::cout << "Bad scene file format" << std::endl;
	std::cout << e.what() << std::endl;
    }
}

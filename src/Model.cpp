#include "Model.h"
#include "foreach.h"
#include <stdio.h>
#include <GL/freeglut.h>


const int maxThreadNumber = 8;


Model::Model() :
    _previousElapsedTime(0), _time(0.0f), _dt(1.0f), _index(new AtomIndex)
{}


Model::~Model()
{
    if (_outputFile.is_open())
	_outputFile.close();
}


void Model::update()
{
    _time += _dt;
    updateLinks();
    updateCollisions();
    updateAtoms();
}


void Model::draw(float width, float height)
{
    glPushMatrix();
    glTranslatef(width / 2.0f, height / 2.0f, 0.0f);
    glScalef(1.0f, -1.0f, 1.0f);

    foreach(Link* link, _links)
	link->draw();

    foreach(Atom* atom, _atoms)
	atom->draw();

    glPopMatrix();

    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    int dt = elapsedTime - _previousElapsedTime;
    _previousElapsedTime = elapsedTime;

    char c[32];
    sprintf(c, "%i", dt);

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(width - 60.0f, height -  10.0f, 0.0f);
    glScalef(0.2f, -0.2f, 1.0f);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)c);
    glPopMatrix();

}


void Model::writeHeader()
{
    if (!_outputFile.is_open())
	return;

    unsigned int numberOfAtoms = _atoms.size();
    float atomRadius = Atom::radius();
    _outputFile.write((char*) &numberOfAtoms, sizeof(numberOfAtoms));
    _outputFile.write((char*) &atomRadius, sizeof(atomRadius));
    foreach(AtomPtr atom, _atoms)
    {
	Color color = atom->color();
	_outputFile.write((char*) &color, sizeof(color));
    }
}


void Model::writeProgress()
{
    if (!_outputFile.is_open())
	return;

    foreach(AtomPtr atom, _atoms)
    {
	Vector position = atom->position();
	_outputFile.write((char*) &position, sizeof(position));
    }
}


void Model::setOutputFile(std::string outputFileName)
{
    if (_outputFile.is_open())
	_outputFile.close();

    _outputFile.open(outputFileName.c_str(), std::ios::out | std::ios::binary);
}


void Model::addBody(Vector position, Vector size,  Vector speed, Color color,
		float density, float linkForce, float linkStretch,
		float linkDamping)
{
    std::vector<Atom*> body;
    size.x = abs(size.x) / 2.0f;
    size.y = abs(size.y) / 2.0f;
    Vector start = position - size;
    Vector end = position + size;
    float offset = 1.0f;
    for (float x = start.x; x <= end.x; x += density)
    {
	for (float y = start.y; y <= end.y; y += density)
	{
	    Atom* atom = new Atom(Vector(x, y + offset * density / 4.0f),
		    speed, color);
	    _atoms.push_back(atom);
	    body.push_back(atom);
	}
	offset = -offset;
    }

    for (unsigned int i = 0; i < body.size() - 1; ++i)
	for (unsigned int j = i + 1; j < body.size(); ++j)
	{
	    Atom* atom1 = body[i];
	    Atom* atom2 = body[j];
	    if (Vector::distance(atom1->position(), atom2->position())
		    <= density * 1.5f)
	    {
		_links.push_back(new Link(atom1, atom2,
			    linkForce, linkStretch, linkDamping));
	    }
	}
}

void Model::updateCollisions()
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / maxThreadNumber + 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(Workers::updateCollisions,
		    _index, from, to, _dt));
	from += atomsPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
}


void Model::updateLinks()
{
    std::vector<boost::thread*> threads;
    unsigned int linksPerThread = _links.size() / maxThreadNumber + 1u;
    auto from = _links.begin();
    auto end = _links.end();
    while (from < end)
    {
	auto to = std::min(end, from + linksPerThread);
	threads.push_back(new boost::thread(Workers::updateLinks,
		    from, to, _dt));
	from += linksPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
}


void Model::updateAtoms()
{
    std::vector<boost::thread*> threads;
    unsigned int atomsPerThread = _atoms.size() / maxThreadNumber + 1u;
    auto from = _atoms.begin();
    auto end = _atoms.end();
    while (from < end)
    {
	auto to = std::min(end, from + atomsPerThread);
	threads.push_back(new boost::thread(Workers::updateAtoms,
		    from, to, _dt));
	from += atomsPerThread;
    }
    foreach(boost::thread* thread, threads)
    {
	thread->join();
	delete thread;
    }
    _index->update(_atoms);
}


float Model::time()
{
    return _time;
}


void Model::setDt(float dt)
{
    _dt = dt;
}

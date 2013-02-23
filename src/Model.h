#ifndef SCENE_H
#define SCENE_H


#include "Vector.h"
#include "Color.h"
#include "Atom.h"
#include "Link.h"
#include "AtomIndex.h"
#include "Workers.h"

#include <vector>
#include <string>
#include <fstream>


class Model
{
    public:
	Model();
	~Model();

	void setOutputFile(std::string outputFileName);

	void update();
	void draw(float width, float height);
	void writeHeader();
	void writeProgress();
	float time();
	void setDt(float dt);
	void addBody(Vector position, Vector size,  Vector speed, Color color,
		float density, float linkForce, float linkStretch,
		float linkDamping);

    private:
	int _previousElapsedTime;
	float _dt;
	float _time;
	std::ofstream _outputFile;

	AtomIndexPtr _index;
	AtomPtrVector _atoms;
	LinkPtrVector _links;


	void updateCollisions();
	void updateLinks();
	void updateAtoms();
};


#endif // SCENE_H

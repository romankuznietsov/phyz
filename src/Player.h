#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include <fstream>
#include <vector>
#include "Vector.h"
#include "Color.h"


class Player
{
    public:
	Player();
	~Player();
	bool loadFile(std::string phyFileName);
	bool nextFrame();
	void display(int windowWidth, int windowHeight);

    private:
	std::ifstream _phyFile;
	unsigned int _numberOfAtoms;
	float _atomRadius;
	std::vector<Vector> _atoms;
	std::vector<Color> _colors;
	bool readHeader();
};


#endif // PLAYER_H

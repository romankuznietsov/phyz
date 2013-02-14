#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include <fstream>
#include <vector>
#include "Vector.h"


class Player
{
    public:
	Player();
	~Player();
	void loadFile(std::string phyFileName);
	bool nextFrame();
	void display(int windowWidth, int windowHeight);

    private:
	std::ifstream phyFile;
	std::vector<Vector> _atoms;
};


#endif // PLAYER_H

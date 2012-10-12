#include "rangedRandom.h"
#include <stdlib.h>
#include <time.h>


void randomize()
{
	static bool alreadyDone = false;
	if (alreadyDone) return;
	alreadyDone = true;
	srand(time(NULL));
}


int rangedRandom(int min, int max)
{
	if (min == max)
		return min;

	if (min > max)
		return rangedRandom(max, min);

	randomize();

	return rand() % (max - min + 1) + min;
}

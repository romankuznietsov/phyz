#include "random.h"
#include "stdlib.h"
#include "time.h"


void randomize()
{
	static bool alreadyDone = false;
	if (alreadyDone) return;
	alreadyDone = true;
	srand(time(NULL));
}


int random(int min, int max)
{
	if (min == max)
		return min;

	if (min > max)
		return random(max, min);

	randomize();

	return rand() % (max - min + 1) + min;
}

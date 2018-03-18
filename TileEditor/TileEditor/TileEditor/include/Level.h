#ifndef LEVEL_H
#define LEVEL_H

#include "Constants.h"

class Level {
public:
	//stuff here
	Level();

	void init();

private:
	int tiles_[NUM_ROWS][NUM_COLUMNS];

	int tileProps_[NUM_ROWS][NUM_COLUMNS];

	int flags_[NUM_ROWS][NUM_COLUMNS];
};

#endif

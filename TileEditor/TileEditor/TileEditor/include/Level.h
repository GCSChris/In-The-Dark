#ifndef LEVEL_H
#define LEVEL_H

#include "Constants.h"

class Level {
public:
	//stuff here
	Level();

	void init();

	int getTileAt(int row, int col);

	int getPropAt(int row, int col);

	int getFlagAt(int row, int col);

	void setTileAt(int row, int col, int data);

	void setPropAt(int row, int col, int data);

	void setFlagAt(int row, int col, int data);

private:
	bool isValidCoords(int row, int col);

	int tiles[NUM_ROWS][NUM_COLUMNS];

	int props[NUM_ROWS][NUM_COLUMNS];

	int flags[NUM_ROWS][NUM_COLUMNS];
};

#endif

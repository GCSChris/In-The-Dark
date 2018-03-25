#ifndef LEVEL_H
#define LEVEL_H

#include "Constants.h"
#include <iostream>

/**
* Represents a level on the tile editor level: levels are divided into three layers to
* differentiate between tiles (visual appearance), props (collision), and flags (spawn, etc.).
*/
class Level {
public:
	
	/**
	* An empty constructor. Levels must be initialized.
	*/
	Level();

	/**
	* Initializes a level.
	*/
	void init();

	/**
	* Gets the tile at the given row and column.
	*/
	int getTileAt(/** The row */ int row, /** The column */ int col);

	/**
	* Gets the prop at the given row and column.
	*/
	int getPropAt(/** The row */ int row, /** The column */ int col);

	/**
	* Gets the flag at the given row and column.
	*/
	int getFlagAt(/** The row */ int row, /** The column */ int col);

	/**
	* Sets the tile at the given row and column to the given piece of data.
	*/
	void setTileAt(/** The row */ int row, /** The column */ int col,  /** The data */ int data);

	/**
	* Sets the prop at the given row and column to the given piece of data.
	*/
	void setPropAt(/** The row */ int row, /** The column */ int col,  /** The data */ int data);

	/**
	* Sets the flag at the given row and column to the given piece of data.
	*/
	void setFlagAt(/** The row */ int row, /** The column */ int col,  /** The data */ int data);

private:
	/**
	* A helper function to determine whether a given set of coordinates is within the allowed 
	* level dimensions.
	*/
	bool isValidCoords(/** The row */ int row, /** The column */ int col);

	/**
	* Renders the tile at the given coordinates.
	*/
	void renderTile(/** The row */ int row, /** The column */ int col);

	/** A 2D array of ints representing tiles. */
	int tiles[NUM_ROWS][NUM_COLUMNS];

	/** A 2D array of ints representing props. */
	int props[NUM_ROWS][NUM_COLUMNS];

	/** A 2D array of ints representing flags. */
	int flags[NUM_ROWS][NUM_COLUMNS];

	/** The number of tiles in the tiles spritesheet. */
	int numTiles = 3; //TODO
	int numProps = 3; //TODO
	int numFlags = 2; //TODO

	void initNumTilesPropsFlags();
};

#endif

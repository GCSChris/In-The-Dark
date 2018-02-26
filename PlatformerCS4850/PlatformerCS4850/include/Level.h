#ifndef LEVEL_H
#define LEVEL_H

#include "Constants.h"

#include <stdexcept>

/** Represents a single level in a game of Breakout */
class Level {
public:
	/** The default constructor */
	Level();

	/** Initializes the Level with the given array of ints */
	void init(/** The int[][] mapping for the level */ int levelMap[MAX_ROWS][MAX_COLUMNS]);

	/** Renders the level */
	void render(/** The renderer to use */ SDL_Renderer* r);

private:

};

#endif

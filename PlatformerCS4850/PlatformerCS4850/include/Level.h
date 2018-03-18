#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Constants.h"
#include "Player.h"

#include <stdexcept>

/** Represents a single level in a game of Breakout */
class Level {
public:
	/** The default constructor */
	Level() {};

	/** Initializes the Level with the given array of ints */
	void init(/** The Tile[][] mapping for the level */ Tile* tiles[MAX_ROWS][MAX_COLUMNS]);

	/** Renders the level */
	void render(/** The renderer to use */ SDL_Renderer* r);

	/** Handles collision with the player and this level if any */
	bool handlePlayerCollisions(Player* player);

private:
	/** Renders the background of the Level */
	void renderBackground(SDL_Renderer* r);

	/** The Tiles for this Level */
	Tile* levelMap[MAX_ROWS][MAX_COLUMNS];
	/** the background texture */
	SDL_Texture* background;
};

#endif

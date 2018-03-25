#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Constants.h"
#include "Player.h"
#include <vector>
#include <stdexcept>

/** Represents a single level in a game of Breakout */
class Level {
public:
	/** The default constructor */
	Level() {};

	/** The destructor */
	~Level();

	/** Initializes the Level with the given array of ints */
	void init(/** The Tile[][] mapping for the level */ Tile* tiles[MAX_ROWS][MAX_COLUMNS],
			  /** The list of GameObjects in this level */ std::vector<GameObject*> objects,
			  /** The player for this level */ Player* player);

	/** Updates the game objects in this level */
	void update();

	/** Renders the level */
	void render(/** The renderer to use */ SDL_Renderer* r);

	/** Handles collision with the player and this level if any */
	bool handlePlayerCollisions();

	/** Returns the Player associated with this level */
	Player* getPlayer();

private:
	/** Renders the background of the Level */
	void renderBackground(SDL_Renderer* r);
	
	/** The player for this level */
	Player* player;
	/** The game objects in this level */
	std::vector<GameObject*> objects;
	/** The Tiles for this Level */
	Tile* levelMap[MAX_ROWS][MAX_COLUMNS];
	/** the background texture */
	SDL_Texture* background;
};

#endif

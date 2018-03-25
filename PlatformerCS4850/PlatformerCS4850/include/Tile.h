#ifndef TILE_H
#define TILE_H

#include "GameObject.h"
#include <string.h>

class Tile : public GameObject {
public:
	/** Initializes this Tile */
	void init(/** The x coordinate */ int x, 
		/** The y coordinate */ int y, 
		/** The sprite sheet to use */ std::string sprSheet, 
		/** The sprite index in the sheet to use */ int sprIndex, 
		/** Whether or not the Tile is collideable */bool collideable);
	/** Renders this Tile */
	void render(/** The renderer to use */SDL_Renderer* ren);

protected:
	/** The SpriteSheet to use for rendering */
	std::string spriteSheet;
	/** The index of the tile to render in the sprite sheet */
	int spriteIndex;
	/** The SDL_Texture to use for rendering */
	SDL_Texture* texture;
};

#endif
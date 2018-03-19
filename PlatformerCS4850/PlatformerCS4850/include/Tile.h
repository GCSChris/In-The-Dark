#ifndef TILE_H
#define TILE_H

#include "GameObject.h"
#include <string.h>

class Tile : public GameObject {
public:
	/** Initializes this Tile */
	void init(int x, int y, std::string sprSheet, int sprIndex, bool collideable);
	/** Renders this Tile */
	void render(SDL_Renderer* ren);

protected:
	/** The SpriteSheet to use for rendering */
	std::string spriteSheet;
	/** The index of the tile to render in the sprite sheet */
	int spriteIndex;
};

#endif
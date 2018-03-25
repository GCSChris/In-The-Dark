#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <string>

#include "../include/Enums.h"

class SpriteSheet {
public:
	/** Initializes the sprite sheet */
	void init(/** The name of the sprite file */std::string fileName,
		/** The width of a tile in the sheet */int tileWidth,
		/** The height of the tile in the sheet */int tileHeight);
	/** Updates the sprite sheet with the given direction */
	void update(Direction dir);
	/** Renders this sprite sheet */
	void render(/** The renderer to use */SDL_Renderer* ren, 
		/** The left x coordinate to render to */int x, 
		/** The upper y coordinate to render to*/int y, 
		/** The width of where to render */int w, 
		/** The height of where to render */int h);

private:
	/** The current animation frame */
	int curAnimationFrame;
	/** The number of frames */
	int numAnimationFrames;
	/** How many ticks have passed in this second */
	int frameTick;
	/** The name of the sprite */
	std::string name;
	/** The texture to render with */
	SDL_Texture* spriteTexture;
	/** The facing direction of the sprite */
	Direction direction;
};

#endif

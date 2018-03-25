#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <string>

#include "../include/Enums.h"

class SpriteSheet {
public:
	void init(std::string fileName, int tileWidth, int tileHeight);
	void update(Direction dir);
	void render(SDL_Renderer* ren, int x, int y, int w, int h);

private:
	int curAnimationFrame;
	int numAnimationFrames;
	int frameTick;
	std::string name;
	SDL_Texture* spriteTexture;
	Direction direction;
};

#endif

#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <string>

#include "../include/Enums.h"

class SpriteSheet {
public:
	void init(int numFrames, std::string fileName);
	void update(Direction dir);
	void render(SDL_Renderer* ren, int x, int y);

private:
	int curAnimationFrame;
	int numAnimationFrames;
	int frameTick;
	std::string name;
	SDL_Texture* spriteTexture;
	Direction direction;
};

#endif

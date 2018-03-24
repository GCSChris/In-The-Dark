#include <SDL.h>

#include "../include/SpriteSheet.h"
#include "../include/Constants.h"
#include "../include/ResourceManager.h"

void SpriteSheet::init(int numFrames, std::string fileName) {
	frameTick = 0;
	curAnimationFrame = 0;
	numAnimationFrames = numFrames;
	name = fileName;
}

void SpriteSheet::update(Direction dir) {
	frameTick++;

	if (frameTick >= FRAMERATE) {
		frameTick = 0;
	}

	if ((frameTick % (FRAMERATE / numAnimationFrames)) == 0) {
		curAnimationFrame++;
	}

	if (curAnimationFrame >= numAnimationFrames) {
		curAnimationFrame = 0;
	}

	direction = dir;
}

void SpriteSheet::render(SDL_Renderer* ren, int x, int y) {
	if (this->spriteTexture == nullptr) {
		this->spriteTexture = ResourceManager::instance().getTexture("./resources/PixelTiger_walk.bmp", ren);
	}

	int srcRectWidth = (curAnimationFrame % numAnimationFrames) * PLAYER_WIDTH;
	int srcRectHeight = (curAnimationFrame / numAnimationFrames) * PLAYER_HEIGHT;

	SDL_Rect src = { srcRectWidth, srcRectHeight, PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_Rect dest = { x, y, PLAYER_WIDTH, PLAYER_HEIGHT };

	SDL_RendererFlip flip = (direction == Direction::LEFT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(ren, spriteTexture, &src, &dest, 0, NULL, flip);
}

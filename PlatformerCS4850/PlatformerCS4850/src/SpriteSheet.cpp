#include <SDL.h>

#include "../include/SpriteSheet.h"
#include "../include/Constants.h"
#include "../include/ResourceManager.h"

void SpriteSheet::init(std::string fileName, int tileWidth, int tileHeight) {
	frameTick = 0;
	curAnimationFrame = 0;
	name = fileName;

	SDL_Point surface = ResourceManager::instance().getIMGDimensions(name);
	int width = surface.x;
	int height = surface.y;
	numAnimationFrames = (width / tileWidth) * (height / tileHeight);
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

void SpriteSheet::render(SDL_Renderer* ren, int x, int y, int w, int h) {
	if (this->spriteTexture == nullptr) {
		this->spriteTexture = ResourceManager::instance().getTexture(name.c_str(), ren);
	}

	int srcRectWidth = (curAnimationFrame % numAnimationFrames) * w;
	int srcRectHeight = (curAnimationFrame / numAnimationFrames) * h;

	SDL_Rect src = { srcRectWidth, srcRectHeight, w, h };
	SDL_Rect dest = { x, y, w, h };

	SDL_RendererFlip flip = (direction == Direction::LEFT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(ren, spriteTexture, &src, &dest, 0, NULL, flip);
}

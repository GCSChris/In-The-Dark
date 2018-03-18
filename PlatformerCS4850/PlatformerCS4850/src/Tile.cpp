#include "../include/Tile.h"

void Tile::init(int x, int y, int w, int h, std::string sprSheet, int sprIndex, bool collideable) {
	GameObject::init(x, y, w, h, collideable);
	spriteSheet = sprSheet;
	spriteIndex = sprIndex;
}

void Tile::render(SDL_Renderer* ren) {
	// TODO insert logic to draw the tile as spriteIndex in the given spriteSheet
	GameObject::render(ren);
}
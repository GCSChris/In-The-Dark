#include "../include/Tile.h"

void Tile::init(int x, int y, std::string sprSheet, int sprIndex, bool collideable) {
	GameObject::init(x, y, TILE_SIZE, TILE_SIZE, collideable);
	spriteSheet = sprSheet;
	spriteIndex = sprIndex;
}

void Tile::render(SDL_Renderer* ren) {
	// TODO insert logic to draw the tile as spriteIndex in the given spriteSheet
	GameObject::render(ren);
}
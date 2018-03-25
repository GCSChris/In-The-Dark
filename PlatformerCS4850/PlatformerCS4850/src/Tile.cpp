#include "../include/Tile.h"
#include "../include/ResourceManager.h"

void Tile::init(int x, int y, std::string sprSheet, int sprIndex, bool collideable) {
	GameObject::init(x, y, TILE_SIZE, TILE_SIZE, collideable);
	spriteSheet = sprSheet;
	spriteIndex = sprIndex;
}

void Tile::render(SDL_Renderer* ren) {
	if (this->texture == nullptr) {
		this->texture = ResourceManager::instance().getTexture(this->spriteSheet.c_str(), ren);
	}
	
	SDL_Rect src = { spriteIndex * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };
	SDL_Rect dst = { x, y, TILE_SIZE, TILE_SIZE };
	SDL_RenderCopy(ren, this->texture, &src, &dst);
}
#include "../include/Level.h"
#include "../include/ResourceManager.h"

void Level::init(Tile* tiles[MAX_ROWS][MAX_COLUMNS]) {
	for (int r = 0; r < MAX_ROWS; r++) {
		for (int c = 0; c < MAX_COLUMNS; c++) {
			levelMap[r][c] = tiles[r][c];
		}
	}
}

void Level::renderBackground(SDL_Renderer* ren) {
	if (this->background == nullptr) {
		this->background = ResourceManager::instance().getTexture("./resources/background.bmp", ren);
	}
	SDL_Rect src = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect dest = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_RenderCopy(ren, this->background, &src, &dest);
}

void Level::render(SDL_Renderer* ren) {
	this->renderBackground(ren);

	for (int r = 0; r < MAX_ROWS; r++) {
		for (int c = 0; c < MAX_COLUMNS; c++) {
			Tile* tile = levelMap[r][c];
			if (tile != nullptr) {
				tile->render(ren);
			}
		}
	}
}

bool Level::handlePlayerCollisions(Player* player) {
	return false;
}
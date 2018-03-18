#include "../include/Level.h"

void Level::init(Tile* tiles[MAX_ROWS][MAX_COLUMNS]) {
	for (int r = 0; r < MAX_ROWS; r++) {
		for (int c = 0; c < MAX_COLUMNS; c++) {
			levelMap[r][c] = tiles[r][c];
		}
	}
}

void Level::render(SDL_Renderer* ren) {
	// TODO render background

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
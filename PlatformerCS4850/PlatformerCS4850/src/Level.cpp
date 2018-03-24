#include "../include/Level.h"
#include "../include/ResourceManager.h"

void Level::init(Tile* tiles[MAX_ROWS][MAX_COLUMNS], std::vector<GameObject*> gameObjects) {
	for (int r = 0; r < MAX_ROWS; r++) {
		for (int c = 0; c < MAX_COLUMNS; c++) {
			levelMap[r][c] = tiles[r][c];
		}
	}
	this->objects = gameObjects;
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
	bool collision = false;

	// Handle collision with the level map
	for (int r = MAX_ROWS - 1; r >= 0; r--) {
		for (int c = 0; c < MAX_COLUMNS; c++) {
			Tile* tile = levelMap[r][c];
			if (tile != nullptr) {
				if (player->isCollidingWithObject(tile)) {
					player->preventCollision(tile);
					collision = true;
				}
			}
		}
	}

	// Handle collision with game objects in the level


	return collision;
}
#include "../include/Level.h"
#include "../include/ResourceManager.h"
#include <iostream>
#include <algorithm>

void Level::init(Tile* tiles[MAX_ROWS][MAX_COLUMNS], std::vector<GameObject*> gameObjects, Player* player) {
	for (int r = 0; r < MAX_ROWS; r++) {
		for (int c = 0; c < MAX_COLUMNS; c++) {
			levelMap[r][c] = tiles[r][c];
		}
	}
	this->player = player;
	this->objects = gameObjects;
}

void Level::renderBackground(SDL_Renderer* ren) {
	if (this->background == nullptr) {
		this->background = ResourceManager::instance().getTexture("./resources/background.png", ren);
	}
	SDL_Rect src = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect dest = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_RenderCopy(ren, this->background, &src, &dest);
}

void Level::update() {
	this->player->update();

	for (const auto& obj : this->objects) {
		obj->update();
		int startingRow = std::max(0, (obj->getY() / TILE_SIZE) - 1);
		int endingRow = std::min(MAX_ROWS, ((obj->getY() + obj->getHeight()) / TILE_SIZE) + 1);
		int startingCol = std::max(0, (obj->getX() / TILE_SIZE) - 1);
		int endingCol = std::min(MAX_COLUMNS, ((obj->getX() + obj->getWidth()) / TILE_SIZE) + 1);
		
		for (int r = endingRow; r > startingRow; r--) {
			for (int c = startingCol; c < endingCol; c++) {
				Tile* tile = this->levelMap[r][c];
				if (tile != nullptr) {
					if (obj->isCollidingWithObject(tile)) {
						obj->preventCollision(tile);
					}
				}
			}
		}
	}

	this->handlePlayerCollisions();
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

	for (const auto& obj : this->objects) {
		obj->render(ren);
	}
	
	player->render(ren);
}

bool Level::handlePlayerCollisions() {
	bool collision = false;

	int startingRow = std::max(0, (player->getY() / TILE_SIZE) - 1);
	int endingRow = std::min(MAX_ROWS, ((player->getY() + player->getHeight()) / TILE_SIZE) + 1);
	int startingCol = std::max(0, (player->getX() / TILE_SIZE) - 1);
	int endingCol = std::min(MAX_COLUMNS, ((player->getX() + player->getWidth()) / TILE_SIZE) + 1);

	// Handle collision with the level map
	for (int r = endingRow; r >= startingRow; r--) {
		for (int c = startingCol; c < endingCol; c++) {
			Tile* tile = levelMap[r][c];
			if (tile != nullptr) {
				if (player->isCollidingWithObject(tile)) {
					player->preventCollision(tile);
					collision = true;
				}
			}
		}
	}

	// Handle collision with enemies in the level
	for (const auto& obj : this->objects) {
		if (obj->isCollidingWithObject(player)) {
			obj->handlePlayerCollision();
		}
	}

	return collision;
}

Player* Level::getPlayer() {
	return this->player;
}
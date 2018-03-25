#include "../include/Level.h"
#include "../include/ResourceManager.h"

Level::Level() {}

void Level::init() {
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLUMNS; j++) {
			tiles[i][j] = 0;
			props[i][j] = 0;
			flags[i][j] = 0;
		}
	}

	initNumTilesPropsFlags();
}

int Level::getTileAt(int row, int col) {
	if(isValidCoords(row, col)) {
		return tiles[row][col];
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

int Level::getPropAt(int row, int col) {
	if (isValidCoords(row, col)) {
		return props[row][col];
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
		return -1;
	}
}

int Level::getFlagAt(int row, int col) {
	if (isValidCoords(row, col)) {
		return flags[row][col];
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
		return -1;
	}
}

void Level::setTileAt(int row, int col, int data) {
	if (isValidCoords(row, col)) {
		if (data > numTiles - 1) {
			data = 0;
		}
		else if (data < 0) {
			data = numTiles - 1;
		}

		tiles[row][col] = data;
		renderTile(row, col);
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

void Level::renderTile(int row, int col) {
}

void Level::setPropAt(int row, int col, int data) {
	if (isValidCoords(row, col)) {
		if (data > numProps - 1) {
			data = 0;
		}
		else if (data < 0) {
			data = numProps - 1;
		}

		props[row][col] = data;
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

void Level::setFlagAt(int row, int col, int data) {
	if (isValidCoords(row, col)) {
		if (data > numFlags - 1) {
			data = 0;
		}
		else if (data < 0) {
			data = numFlags - 1;
		}

		flags[row][col] = data;
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

bool Level::isValidCoords(int row, int col) {
	return col >= 0 && col < NUM_COLUMNS && row >= 0 && row < NUM_ROWS;
}

void Level::initNumTilesPropsFlags() {
	SDL_Point tilesDimensions = ResourceManager::instance().getIMGDimensions(TILES_SPRITE_SHEET);
	SDL_Point propsDimensions = ResourceManager::instance().getIMGDimensions(PROPS_SPRITE_SHEET);
	SDL_Point flagsDimensions = ResourceManager::instance().getIMGDimensions(FLAGS_SPRITE_SHEET);

	numTiles = tilesDimensions.x / TILE_SIZE;
	numProps = propsDimensions.x / TILE_SIZE;
	numFlags = flagsDimensions.x / TILE_SIZE;
}
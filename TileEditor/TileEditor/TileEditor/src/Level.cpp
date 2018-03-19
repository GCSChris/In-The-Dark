#include "../include/Level.h"
#include <iostream>

Level::Level() {}

const int TILES_MAX = 3;
const int PROPS_MAX = 4;
const int FLAGS_MAX = 5;

void Level::init() {
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLUMNS; j++) {
			tiles[i][j] = 0;
			props[i][j] = 0;
			flags[i][j] = 0;
		}
	}
}

int Level::getTileAt(int row, int col) {
	if(isValidCoords(row, col)) {
		printf("returning %i\n", tiles[row][col]);
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
		if (data > TILES_MAX) {
			data = 0;
		}
		else if (data < 0) {
			data = TILES_MAX;
		}

		std::cout << "set tile at " << row << ", " << col << " to " << data << std::endl;
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
		if (data > PROPS_MAX) {
			data = 0;
		}
		else if (data < 0) {
			data = PROPS_MAX;
		}

		std::cout << "set prop at " << row << ", " << col << " to " << data << std::endl;
		props[row][col] = data;
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

void Level::setFlagAt(int row, int col, int data) {
	if (isValidCoords(row, col)) {
		if (data > FLAGS_MAX) {
			data = 0;
		}
		else if (data < 0) {
			data = FLAGS_MAX;
		}

		std::cout << "set flag at " << row << ", " << col << " to " << data << std::endl;
		flags[row][col] = data;
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

bool Level::isValidCoords(int row, int col) {
	return col >= 0 && col < NUM_COLUMNS && row >= 0 && row < NUM_ROWS;
}

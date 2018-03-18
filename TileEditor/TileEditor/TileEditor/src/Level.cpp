#include "../include/Level.h"
#include <iostream>

Level::Level() {}

void Level::init() {

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
	}
}

int Level::getFlagAt(int row, int col) {
	if (isValidCoords(row, col)) {
		return flags[row][col];
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

void Level::setTileAt(int row, int col, int data) {
	if (isValidCoords(row, col)) {
		tiles[row][col] = data;
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

void Level::setPropAt(int row, int col, int data) {
	if (isValidCoords(row, col)) {
		props[row][col] = data;
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

void Level::setFlagAt(int row, int col, int data) {
	if (isValidCoords(row, col)) {
		flags[row][col] = data;
	}
	else {
		std::cerr << "Invalid indices" << std::endl;
	}
}

bool Level::isValidCoords(int row, int col) {
	return col >= 0 && col < NUM_COLUMNS && row >= 0 && row < NUM_ROWS;
}

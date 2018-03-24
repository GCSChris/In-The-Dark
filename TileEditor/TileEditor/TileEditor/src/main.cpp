#include "../include/TileEditor.h"
#include "../include/Parser.h"
#include "../include/Level.h"
#include "../include/Constants.h"
#include <iostream>

int main() {
	/*
	TileEditor* te = new TileEditor();

	te->init();

	te->play();

	*/

	Level l = Parser::instance().loadLevel("resources/Level1.txt");

	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			std::cout << l.getTileAt(r, c);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			std::cout << l.getPropAt(r, c);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			std::cout << l.getFlagAt(r, c);
		}
		std::cout << std::endl;
	}

	std::getchar();

	return 0;
}

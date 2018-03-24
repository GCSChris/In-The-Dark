#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include "Constants.h"
#include "Level.h"

class Parser {
public:
	static Parser& instance() {
		static Parser *instance = new Parser();
		return *instance;
	}

	Level loadLevel() {
		std::ifstream levelFile; // open a new ifstream
		int tile; // temporary hold for date 
		bool tilesInit = false;
		bool propsInit = false;
		bool flagsInit = false; // bool flags

		// initialize a new level
		Level* loaded = new Level();
		loaded->init();

		// tile parsing
		levelFile.open(fileLocation);
		if (!levelFile) {
			std::cout << "Unable to open file." << std::endl;
			exit(1);
		}
		else {
			// read char by char
			char c;
			int index = 0;
			while (levelFile >> std::skipws >> c) {
				if (c == 'X') {
					if (!tilesInit) {
						tilesInit = true;
						index = 0;
					}
					else if (!propsInit) {
						propsInit = true;
						index = 0;
					}
					else if (!flagsInit) {
						flagsInit = true;
						index = 0;
					}
				}
				else {
					tile = c - '0';
					if (!tilesInit) {
						loaded->setTileAt(index / NUM_COLUMNS, index % NUM_COLUMNS, tile);
					} 
					else if (!propsInit) {
						loaded->setPropAt(index / NUM_COLUMNS, index % NUM_COLUMNS, tile);
					}
					else if (!flagsInit) {
						loaded->setFlagAt(index / NUM_COLUMNS, index % NUM_COLUMNS, tile);
					}
					else {
						// everything has been initialized
						break;
					}

					index++;
				}
			}
		}

		// check to make sure everything was initialized
		if (!(tilesInit && propsInit && flagsInit)) {
			std::cout << "Malformed file. Could not load" << std::endl;
			exit(1);
		}

		levelFile.close();

		return *loaded;
	}

	void writeLevel(Level* level) {
		std::ofstream myFile;

		myFile.open(fileLocation);

		for (int r = 0; r < NUM_ROWS; r++) {
			for (int c = 0; c < NUM_COLUMNS; c++) {
				myFile << level->getTileAt(r, c) << " ";
			}
			myFile << "\n";
		}
		myFile << "X\n";

		for (int r = 0; r < NUM_ROWS; r++) {
			for (int c = 0; c < NUM_COLUMNS; c++) {
				myFile << level->getPropAt(r, c) << " ";
			}
			myFile << "\n";
		}
		myFile << "X\n";

		for (int r = 0; r < NUM_ROWS; r++) {
			for (int c = 0; c < NUM_COLUMNS; c++) {
				myFile << level->getFlagAt(r, c) << " ";
			}
			myFile << "\n";
		}
		myFile << "X\n";

		myFile.close();
	}

private:
	Parser() {};

	std::string fileLocation = "resources/Level1.txt";
};

#endif

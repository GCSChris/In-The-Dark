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

	void loadLevel(std::string levelFilePath) {
		std::ifstream levelFile; // open a new ifstream
		int tile; // temporary hold for date 
		bool tilesInit, propsInit, flagsInit = false; // bool flags

		// initialize a new level
		Level* loaded = new Level();
		loaded->init();

		// tile parsing
		levelFile.open(levelFilePath);
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
	}

	void writeLevel() {

	}

private:
	Parser() {};

};

#endif

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
		std::ifstream levelFile;
		std::string temp;
		int tile;

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
			
		}
	}

	void writeLevel() {

	}

private:
	Parser() {};

};

#endif

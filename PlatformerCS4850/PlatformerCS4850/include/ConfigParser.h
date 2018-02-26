#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "Level.h"

/** A singleton class to handle the parsing of level building scripts and game settings. */
class ConfigParser {
public:
	/** Get the instance of this singleton. */
	static ConfigParser& instance() {
		if (inst_ == NULL) {
			inst_ = new ConfigParser();
		}
		return *inst_;
	}

	/** Parse the game config file for game settings. */
	void parseGameConfig() {
		// open file
		std::ifstream input;
		std::string fileName = "game_config.txt";
		input.open(fileName);
		if (!input) {
			std::cerr << "Error: couldn't open config" << std::endl;
			exit(1);
		}

		// read in lines until end of file
		std::string line;
		while (std::getline(input, line)) {
			int delim = line.find("=");
			std::string key = line.substr(0, delim);
			std::string value = line.substr(delim + 1, line.length());
			settings.insert(std::pair<std::string, std::string>(key, value));
		}

		input.close();
	}

	/** Parse the level script to build the levels. */
	void parseLevel(/** The file to parse for levels.*/std::string filePath) {
		std::ifstream configFile;
		std::string temp;
		int brick, numLevels = 0;

		int lvl[MAX_ROWS][MAX_COLUMNS];

		configFile.open(filePath);
		if (!configFile) {
			std::cout << "Unable to open file";
			exit(1);
		}

		while (std::getline(configFile, temp)) {
			
			if (temp == LEVEL_START_TAG) {
				++numLevels;
				for (int r = 0; r < MAX_ROWS; r++) {
					for (int c = 0; c < MAX_COLUMNS; c++) {
						configFile >> brick;
						lvl[r][c] = brick;
					}
				}
			}
			else if (temp == LEVEL_END_TAG) {
				Level* l = new Level();
				l->init(lvl);

				levels.push_back(l);
			}
		}

		configFile.close();
	}

	/** Get a particular level at the given index. */
	Level* getLevel(/** The index of the level to get. */ int index) {
		try {
			return levels.at(index);
		}
		catch (std::out_of_range e) {
			return nullptr;
		}
	}

	/** Returns if a level exist at the given index. */
	bool hasNextLevel(/** The index of the level check. */ int index) {
		return index < levels.size();
	}

	/** */
	std::string getSetting(std::string str, std::string defValue) {
		if (settings.count(str) > 0) {
			return settings[str];
		}
		return defValue;
	}

	void clearLevels() {
		levels.clear();
	}

private:
	/** Default constructor for ConfigParser. */
	ConfigParser() {}

	/** Default destructor for ConfigParser. */
	~ConfigParser() {}

	/** The singleton instance */
	static ConfigParser* inst_;

	/** The vector of levels parsed by this ConfigParser. */
	std::vector<Level*> levels = {};

	/** Map of settings parsed from game config. */
	std::map<std::string, std::string> settings;

	/** Constant representing the level start tag 
	  (used to mark start of a level in parsing level script).*/
	const std::string LEVEL_START_TAG = "LEVEL_START";

	/** Constant representing the level end tag 
	  (used to mark end of a level in parsing level script).*/
	const std::string LEVEL_END_TAG = "LEVEL_END";
};

#endif

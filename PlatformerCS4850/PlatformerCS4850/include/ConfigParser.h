#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "Level.h"
#include "Player.h"
#include "Battery.h"
#include "Rocket.h"
#include "Enemy.h"
#include "GameObject.h"

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
	Level* parseLevel(/** The file to parse for levels.*/std::string filePath) {
		std::ifstream levelFile; // open a new ifstream
		bool tilesInit = false;
		bool propsInit = false;
		bool flagsInit = false; // bool flags

								// initialize a new level
		Level* level = new Level();

		// tile parsing
		levelFile.open(filePath);
		
		int tileSprites[MAX_ROWS][MAX_COLUMNS];
		int tileProps[MAX_ROWS][MAX_COLUMNS];
		int flags[MAX_ROWS][MAX_COLUMNS];

		Tile* tiles[MAX_ROWS][MAX_COLUMNS];
		std::vector<GameObject*> gameObjects;
		Player* player;

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
					int value = c - '0';
					if (!tilesInit) {
						tileSprites[index / MAX_COLUMNS][index % MAX_COLUMNS] = value;
					}
					else if (!propsInit) {
						tileProps[index / MAX_COLUMNS][index % MAX_COLUMNS] = value;
					}
					else if (!flagsInit) {
						int x = index / MAX_COLUMNS;
						int y = index / MAX_ROWS;
						GameObject* go = this->createGameObject(value, x, y);
						if (value == 1 && player == nullptr) {
							Player* player = new Player();
							player->init(x, y, 4, "./resources/PixelTiger_walk.png");
						}
						else if (go == nullptr) {
							gameObjects.push_back(go);
						}
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

		// Arrays are parsed, time to create the tile mapping
		for(int r = 0; r < MAX_ROWS; r++) {
			for (int c = 0; c < MAX_COLUMNS; c++) {
				if (tileSprites[r][c] == 0) {
					tiles[r][c] = nullptr;
				}
				else {
					Tile* tile = new Tile();
					tile->init(c * TILE_SIZE, r * TILE_SIZE, "./resources/tileset.png", tileSprites[r][c], tileProps[r][c]);
					tiles[r][c] = tile;
				}
			}
		}

		level->init(tiles, gameObjects, player);

		return level;
	}

	/** Returns the setting from the parsed settings if possible, otherwise the default */
	std::string getSetting(/** The setting to get */std::string str,
		/** The fall back value */std::string defValue) {
		if (settings.count(str) > 0) {
			return settings[str];
		}
		return defValue;
	}

	/** Creates and returns a pointer to a game object */
	GameObject* createGameObject(/** The parsed valueof the object from the level */int objectValue, 
		/** The left x-coordinate */int x, 
		/** The upper y-coordinate */int y) {

		Enemy* enemy;
		Battery* battery;
		Rocket* rocket;

		switch (objectValue) {
			case 0:
			case 1:
				return nullptr;
			case 2:
				enemy = new Enemy();
				enemy->init(x, y, ENEMY_WIDTH, ENEMY_HEIGHT, 4, "./resources/Angry_Wolf.png");
				return enemy;
				break;
			case 3:
				battery = new Battery();
				battery->init(x, y, TILE_SIZE, TILE_SIZE, "./resources/battery.png");
				return battery;
				break;
			case 4:
				rocket = new Rocket();
				rocket->init(x, y, TILE_SIZE, TILE_SIZE, "./resources/rocket.png");
				return rocket;
			default:
				return nullptr;
		}
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

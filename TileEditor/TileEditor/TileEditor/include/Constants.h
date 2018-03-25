#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>
#include <string>

// size of 1 side of a tile in pixels
const int TILE_SIZE = 16;

const int NUM_COLUMNS = 80;

const int NUM_ROWS = 45;

const int FRAMERATE = 60;

const SDL_Color GRID_COLOR = { 30, 161, 170, 255 };

const int BOTTOM_BUFFER = 32;

const int SIDE_BUFFER = 16;

enum class EditMode {
	TILES, PROPS, FLAGS
};

const char LAYER_TAG = 'X';

const std::string DEFAULT_TEXT_FONT_STYLE = "./resources/arial.ttf";

const int DEFAULT_TEXT_FONT_SIZE = 16;

const SDL_Color DEFAULT_TEXT_FONT_COLOR = { 255, 255, 255, 255 };

#endif

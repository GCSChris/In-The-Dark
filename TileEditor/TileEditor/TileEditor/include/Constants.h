#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>
#include <string>

/** size of 1 side of a tile in pixels */
const int TILE_SIZE = 16;

/** The number of columns of tiles per row */
const int NUM_COLUMNS = 80;

/** The number of rows of tiles per column */
const int NUM_ROWS = 45;

/** The framerate to lock gameplay at. */
const int FRAMERATE = 60;

/** The color of the grid distinguishing seperate tiles in the tile editor. */
const SDL_Color GRID_COLOR = { 30, 161, 170, 255 };

/** The amount of extra space below the grid of tiles in pixels */
const int BOTTOM_BUFFER = 32;

/** The amount of extra space on each side of the grid of tiles in pixels */
const int SIDE_BUFFER = 16;

/**
* This enum represents the three different edit modes of the tile editor.
*/
enum class EditMode {
	TILES, PROPS, FLAGS
};

/** The character that denotes the end of one layer in the level text file */
const char LAYER_TAG = 'X';

/** The font used for writing text */
const std::string DEFAULT_TEXT_FONT_STYLE = "./resources/arial.ttf";

/** The font size used for writing text */
const int DEFAULT_TEXT_FONT_SIZE = 16;

/** The font color used for writing text */
const SDL_Color DEFAULT_TEXT_FONT_COLOR = { 255, 255, 255, 255 };

#endif

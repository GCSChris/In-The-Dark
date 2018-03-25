#ifndef TILE_EDITOR_H
#define TILE_EDITOR_H

#include <SDL.h>
#undef main
#include <string>
#include <sstream>
#include <iostream>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Button.h"
#include "SaveLoadButtons.h"
#include "Level.h"

/**
* The main tile editor class which handles creating, rendering, and looping through the tile editor.
*/
class TileEditor {
public:
	/**
	* Empty constructor (must call init).
	*/
	TileEditor();

	/**
	* Safely deletes a tile editor once it is finished being used.
	*/
	~TileEditor();

	/**
	* Initializes the tile editor.
	*/
	void init();

	/**
	* continuously plays the tile editor while the program is still running.
	*/
	void play();

	/**
	* Updates the tile editor as needed.
	*/
	void update();

	/**
	* Renders the tile editor.
	*/
	void render();

private:

	/**
	* Edits a specific tile.
	*/
	void editTile(/** The tile's row */ int tileRow, /** The tile's column */int tileColumn, 
		/** whether the click event was a left mouse click */ bool leftClick);

	/**
	* Increments a tile value on a left click and decrements on a right click.
	*/
	int editTileVal(/** The tile's current value */ int tileVal, 
		/** whether the click event was a left mouse click */ bool leftClick);
	
	/**
	* Draws a grid over the tile editor for clarity.
	*/
	void drawGrid();

	/**
	* Handles user input.
	*/
	bool handleKeyboard(/** The type of input */ SDL_Event e);

	/**
	* Renders all tiles in the grid.
	*/
	void renderTiles();

	/**
	* Renders a single tile at the given row and column.
	*/
	void renderTile(/** the row */ int r, /** The column */ int c);

	/**
	* Renders the background image.
	*/
	void renderBg();

	/**
	* The total screen width.
	*/
	int screenWidth = TILE_SIZE*NUM_COLUMNS + 2*SIDE_BUFFER;

	/**
	* The total screen width.
	*/
	int screenHeight = TILE_SIZE*NUM_ROWS + 2*SIDE_BUFFER + BOTTOM_BUFFER;

	/**
	* The current level represented in the level editor.
	*/
	Level* level;

	/**
	* The SDL window.
	*/
	SDL_Window* gWindow;

	/**
	* The SDL renderer
	*/
	SDL_Renderer* gRenderer;

	/**
	* The tile button
	*/
	Button* buttonOne;

	/**
	* The prop button
	*/
	Button* buttonTwo;

	/**
	* The flag button
	*/
	Button* buttonThree;

	/**
	* The load level button
	*/
	SaveLoadButtons* buttonFour;

	/**
	* The save level button
	*/
	SaveLoadButtons* buttonFive;

	/**
	* The edit mode the editor is currently in
	*/
	EditMode currentEditMode;

	/**
	* A flag for whether the tiles have been updated
	*/
	bool tilesUpdated = false;

};

#endif

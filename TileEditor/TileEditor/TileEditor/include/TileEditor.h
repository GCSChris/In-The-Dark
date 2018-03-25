#ifndef TILE_EDITOR_H
#define TILE_EDITOR_H

#include <SDL.h>
#undef main
#include <string>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Button.h"
#include "SaveLoadButtons.h"
#include "Level.h"

class TileEditor {
public:
	TileEditor();

	~TileEditor();

	void init();

	void play();

	void update();

	void render();

private:

	void editTile(int tileRow, int tileColumn, bool leftClick);

	int editTileVal(int tileVal, bool leftClick);

	void drawGrid();

	bool handleKeyboard(SDL_Event e);

	void renderTiles();

	void renderTile(int r, int c);

	void renderBg();

	int screenWidth = TILE_SIZE*NUM_COLUMNS + 2*SIDE_BUFFER;
	int screenHeight = TILE_SIZE*NUM_ROWS + 2*SIDE_BUFFER + BOTTOM_BUFFER;

	Level* level;

	SDL_Window* gWindow;

	SDL_Renderer* gRenderer;

	Button* buttonOne;
	Button* buttonTwo;
	Button* buttonThree;
	SaveLoadButtons* buttonFour;
	SaveLoadButtons* buttonFive;

	EditMode currentEditMode;

	bool tilesUpdated = false;

	SDL_Texture* bigTexture;

};

#endif

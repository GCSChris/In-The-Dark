#ifndef TILE_EDITOR_H
#define TILE_EDITOR_H

#include <SDL.h>
#undef main
#include <string>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Button.h"
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
	// SDL_Point getMouseClick
	void editTile(int tileRow, int tileColumn, bool leftClick);

	int editTileVal(int tileVal, bool leftClick);

	void drawGrid();

	bool handleKeyboard(SDL_Event e);

	void renderTiles();
	void renderTile(int r, int c);
	//void renderTileHelp(int r, int c);
	//void renderRectangle(SDL_Rect* rect, SDL_Color color);

	int screenWidth = TILE_SIZE*NUM_COLUMNS + 2*SIDE_BUFFER;
	int screenHeight = TILE_SIZE*NUM_ROWS + 2*SIDE_BUFFER + BOTTOM_BUFFER;

	Level* level;

	SDL_Window* gWindow;

	SDL_Renderer* gRenderer;

	Button* buttonOne;
	Button* buttonTwo;
	Button* buttonThree;

	EditMode currentEditMode;

	bool tilesUpdated = false;

	SDL_Texture* bigTexture;

	void UpdateTexture(SDL_Texture* texture, int x, int y);
};

#endif

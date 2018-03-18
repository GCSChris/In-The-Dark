#ifndef TILE_EDITOR_H
#define TILE_EDITOR_H

#include <SDL.h>
#undef main
#include <string>
#include <SDL_ttf.h>
#include "Constants.h"


class TileEditor {
public:
	TileEditor();

	~TileEditor();

	void init();

	void play();

	void update();

	void render();

private:
	void drawGrid();

	bool handleKeyboard(SDL_Event e);

	int screenWidth = TILE_SIZE*NUM_COLUMNS + 2*SIDE_BUFFER;
	int screenHeight = TILE_SIZE*NUM_ROWS + 2*SIDE_BUFFER + BOTTOM_BUFFER;

	SDL_Window* gWindow;

	SDL_Renderer* gRenderer;
};

#endif

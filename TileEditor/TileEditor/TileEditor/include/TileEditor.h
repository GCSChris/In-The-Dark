#ifndef TILE_EDITOR_H
#define TILE_EDITOR_H

#include <SDL.h>

class TileEditor {
public:
	TileEditor();

	~TileEditor();

	void init();

private:
	int screenWidth = 1280;
	int screenHeight = 720;

	SDL_Window* gWindow;

	SDL_Renderer* gRenderer;
};

#endif


#include "../include/TileEditor.h"

TileEditor::TileEditor() { }

TileEditor::~TileEditor() { }

void TileEditor::init() {
	gWindow = SDL_CreateWindow("Breakout",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN);
}

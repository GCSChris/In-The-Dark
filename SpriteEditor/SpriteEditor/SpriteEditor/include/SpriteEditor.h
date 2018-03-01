#ifndef SPRITE_EDITOR_H
#define SPRITE_EDITOR_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#undef main

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

class SpriteEditor {
public:
	/** Constructor for a SpriteEditor. */
	SpriteEditor();

	/** Default destructor for a SpriteEditor. */
	~SpriteEditor();

	/** TODO */
	bool init();

private:
	SDL_Window* gWindow;
	/** SDL Renderer to use. */
	SDL_Renderer* gRenderer = NULL;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;
};

#endif
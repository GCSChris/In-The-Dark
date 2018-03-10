//#pragma once
#ifndef SPRITE_EDITOR_H
#define SPRITE_EDITOR_H

#include <SDL.h>
#undef main

#include <SDL_image.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

//#define FRAME_WIDTH 20
//#define FRAME_HEIGHT 30 TODO

// smooth 60fps
#define FRAMERATE 60 //TODO change back to 60

/** Represent a sprite editor. */
class SpriteEditor {
public:
	/** Constructor for a BreakoutGame. */
	SpriteEditor(/** The width to use for the frame. */ int w,
		/** The height to use for the frame. */ int h,
		/** TODO */ int frames);

	/** Default destructor for a BreakoutGame. */
	~SpriteEditor();

	/** Function that starts a game of breakout! */
	void play();

private:
	/** Handles initilization of the game. */
	void start();

	/** Updates the game state every frame. */
	void update();

	/** Renders game elements to the screen every frame. */
	void render();

	/** Get Pointer to SDL Window. */
	SDL_Window* getSDLWindow();

	/** Get Pointer to SDL Renderer */
	SDL_Renderer* getSDLRenderer();

	/** Handle keyboard input from the user. */
	bool handleKeyboard(/** The keyboard event to handle. */ SDL_Event e);

	/** The width of the screen for the game. */
	int frameWidth;
	/** The height of the screen for the game. */
	int frameHeight;
	/** TODO*/
	int numFrames;

	/** The window we'll be rendering to. */
	SDL_Window* gWindow;
	/** SDL Renderer to use. */
	SDL_Renderer* gRenderer = NULL;

	int currentFrame = 0;
};

#endif

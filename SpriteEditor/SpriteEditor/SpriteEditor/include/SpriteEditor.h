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

/** Represent a sprite editor. */
class SpriteEditor {
public:
	/** Default constructor for a SpriteEditor. */
	SpriteEditor();

	/** Default destructor for a SpriteEditor. */
	~SpriteEditor();

	/** Initialize a SpriteEditor. */
	void init();

	/** Clean up when SpriteEditor is ready to be deleted. */
	void cleanUp();

	/** Starts the SpriteEditor. */
	void run();

private:
	/** Updates the game state every frame. */
	void update();

	/** Renders game elements to the screen every frame. */
	void render();

	/** Handle keyboard input from the user. */
	bool handleKeyboard(/** The keyboard event to handle. */ SDL_Event e);

	/** Set up the SpriteEditor using the values specfied through the command line form the user. */
	void configureFromUserInput();
	
	/** Get Pointer to SDL Window. */
	SDL_Window* getSDLWindow();

	/** Get Pointer to SDL Renderer */
	SDL_Renderer* getSDLRenderer();

	/** */
	std::string fileName;
	
	/** The width of one frame of the spritesheet. */
	int frameWidth;
	
	/** The height of one frame of the spritesheet. */
	int frameHeight;
	
	/** The total number of frames in the spritesheet. */
	int numFrames;
	
	void setNumColumns();
	/** The number columns in the spritesheet. */
	int numColumns;

	/** The desired frameRate to run the animation of the spritesheet. */
	int frameRate;

	/** The window we'll be rendering to. */
	SDL_Window* gWindow;
	/** SDL Renderer to use. */
	SDL_Renderer* gRenderer = NULL;

	/** Counter to determine which frame to render. */
	int currentFrame = 0;

	/** The directory to pull images from. */
	std::string resources_directory;

	/** Counter for current frame in a second */
	int frame = 0;
};

#endif

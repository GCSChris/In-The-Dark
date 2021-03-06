#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SDL.h>
#undef main

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "Level.h"
#include "Constants.h"
#include "Player.h"
#include "UIManager.h"
#include "SFXManager.h"
#include "ConfigParser.h"
#include "VisibleCircle.h"

// smooth 60fps
#define FRAMERATE 60

/** Represent a platformer game. */
class PlatformerGame {
public:
    /** Constructor for a PlatformerGame. */
	PlatformerGame(/** The width to use for the game window. */int w = SCREEN_WIDTH,
		/** The height to use for the game window. */int h = SCREEN_HEIGHT);
	
	/** Default destructor for a PlatformerGame. */
    ~PlatformerGame();
    
	/** Function that starts a platformer game! */
    void play();

private:
	/** Handles initilization of the game. */
	void startGame();
	void restartGame();

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
	
	/** Check if the game is lost. */
	void checkGameLoss();

	/** Pause/Unpause the game. */
	void togglePause();

    /** The height of the screen for the game. */
	int screenHeight;
	/** The width of the screen for the game. */
	int screenWidth;
	
	/** The visibility Circle */
	VisibleCircle* visibilityCircle;

	/** UI Manager - used to render UI elements. */
	UIManager* uiManager;
	/** SFX Manager - used to manage playing of sound effects. */
	SFXManager* sfxManager;

	/** The instance of a config parser - used to parse our game config and level scripts. */
	ConfigParser &cp = ConfigParser::instance();
	
	/** Game Status - holds info like lives, score, etc. */
	GameStatus* gameStatus;
	
	/** The currrent level being played. */
	Level* level;
	/** The index of the current level being played. */
	int curLevel;

	/** The window we'll be rendering to. */
	SDL_Window* gWindow;
	/** SDL Renderer to use. */
	SDL_Renderer* gRenderer = NULL;
};

#endif

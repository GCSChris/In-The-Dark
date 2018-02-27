#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SDL.h>
#undef main

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "Level.h"
#include "Constants.h"
#include "Paddle.h"
#include "Ball.h"
#include "UIManager.h"
#include "SFXManager.h"
#include "ConfigParser.h"

/** Represent a game of breakout. */
class BreakoutGame {
public:
    /** Constructor for a BreakoutGame. */
	BreakoutGame(/** The width to use for the game window. */int w = SCREEN_WIDTH, 
		/** The height to use for the game window. */int h = SCREEN_HEIGHT);
	
	/** Default destructor for a BreakoutGame. */
    ~BreakoutGame();
    
	
    
	/** Function that starts a game of breakout! */
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

	/** Transition to next level. Returns true if there is a
	next level, false if there are no remaiing levels. */
	bool getNextLevel();

	/** Move the ball if it is not frozen. */
	void handleFrozenBall();
	/** Move the ball if it is not frozen. */
	void handleCollisions();

	/** Handles ending the game if it is flagged to be over. */
	void handleGameOver();

	/** Pause/Unpause the game. */
	void togglePause();

    /** The height of the screen for the game. */
	int screenHeight;
	/** The width of the screen for the game. */
	int screenWidth;
	
	/** The user's paddle */
	Paddle* paddle;
	/** The ball. */
	Ball* ball;
	
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
#include <ctime>
#include "../include/BreakoutGame.h"
#include "../include/Rectangle.h"
#include "../include/Level.h"
#include "../include/ConfigParser.h"
#include "../include/GameStatus.h"

#include <SDL_ttf.h>
#include <string>

#include <thread>
#include <chrono>

// smooth 60fps
#define FRAMERATE 60

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
BreakoutGame::BreakoutGame(int w, int h) :screenWidth(w), screenHeight(h) {
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	gWindow = NULL;
	// Render flag
	TTF_Init();

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
		//Create window
		gWindow = SDL_CreateWindow("Breakout",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screenWidth,
			screenHeight,
			SDL_WINDOW_SHOWN);

		// Check if Window did not create.
		if (gWindow == NULL) {
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create a Renderer to draw on
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		// Check if Renderer did not create.
		if (gRenderer == NULL) {
			errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}
	}

	// If initialization did not work, then print out a list of errors in the constructor.
	if (!success) {
		errorStream << "Failed to initialize!\n";
		std::string errors = errorStream.str();
		std::cout << errors << "\n";
	}
	else {
		std::cout << "No SDL or OpenGL errors Detected\n\n";
	}
	
	startGame();
}

void BreakoutGame::startGame() {
	// Initialize game elements
	gameStatus = new GameStatus;
	int lives = std::stoi(ConfigParser::instance().getSetting("lives", "3"));
	gameStatus->init(lives, 0);

	paddle = new Paddle;
	paddle->init();

	ball = new Ball;
	ball->init(gRenderer, gameStatus);

	uiManager = new UIManager;
	uiManager->init(gameStatus);

	SFXManager::instance().playMusic("./resources/music.wav");
	
	ConfigParser::instance().parseLevel("lvlconfig.txt");
	//levels = ConfigParser::instance().getLevels();
	curLevel = 0;
	level = ConfigParser::instance().getLevel(curLevel);
}

void BreakoutGame::restartGame() {
	ConfigParser::instance().clearLevels();
	ConfigParser::instance().parseLevel("lvlconfig.txt");

	curLevel = 0;
	level = ConfigParser::instance().getLevel(curLevel);
	int lives = std::stoi(ConfigParser::instance().getSetting("lives", "3"));
	gameStatus->init(lives, 0);
	ball->resetBall();
}

// Proper shutdown and destroy initialized objects
BreakoutGame::~BreakoutGame() {
	// Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	//Destroy window
	SDL_DestroyWindow(gWindow);
	// Point gWindow to NULL to ensure it points to nothing.
	gRenderer = NULL;
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
}

// Update OpenGL
void BreakoutGame::update() {
	paddle->update();
	
	handleFrozenBall();
	
	SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
	SDL_RenderClear(gRenderer);
	
	handleGameOver();

	if (level->isCleared()) {
		//win level logic

		if (!getNextLevel()) {
			gameStatus->gameOver = true;
			gameStatus->gameWon = true;
		}
	}
	
}

void BreakoutGame::handleGameOver() {
	if (gameStatus->lives <= 0) {
		gameStatus->gameOver = true;
		gameStatus->gameWon = false;
	}
}

void BreakoutGame::handleFrozenBall() {
	if (gameStatus->ballFrozenCount == 0) {
		ball->update();
		handleCollisions();
	}
	else {
		gameStatus->ballFrozenCount++;
	}
	if (gameStatus->ballFrozenCount > (BALL_FREEZE_SECONDS * FRAMERATE)) {
		gameStatus->ballFrozenCount = 0;
	}
}

// Render
// The render function gets called once per loop
void BreakoutGame::render() {
	level->render(getSDLRenderer());
	paddle->render(getSDLRenderer());
	ball->render(getSDLRenderer());
	uiManager->render(getSDLRenderer());
	
	SDL_RenderPresent(gRenderer);
}

//Loops forever!
void BreakoutGame::play() {
	// Main loop flag
	// If this is quit = 'true' then the program terminates.
	bool quit = false;
	// Event handler that handles various events in SDL
	// that are related to input and output
	SDL_Event e;
	// Enable text input
	SDL_StartTextInput();
	// While application is running
	while (!quit) {
		Uint32 start = SDL_GetTicks();
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			// User posts an event to quit
			// An example is hitting the "x" in the corner of the window.
			quit = handleKeyboard(e);

			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		
		if (!gameStatus->isPaused && !gameStatus->gameOver) {
			update();
		}

		// Render using OpenGL
		render();
		//Update screen of our specified window
		SDL_GL_SwapWindow(getSDLWindow());
		
		// Delay to force 60 FPS
		int diff = SDL_GetTicks() - start;
		float delay = 1000.0f / FRAMERATE - diff;
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}

	//Disable text input
	SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* BreakoutGame::getSDLWindow() {
	return gWindow;
}

// Get Pointer to Renderer
SDL_Renderer* BreakoutGame::getSDLRenderer() {
	return gRenderer;
}

bool BreakoutGame::handleKeyboard(SDL_Event e) {
	if (e.type == SDL_KEYUP) {
		SDL_Keycode keyPressed = e.key.keysym.sym;

		if (keyPressed == SDLK_a && paddle->getSpeedX() < 0) {
			paddle->setSpeedX(0);
		}
		if (keyPressed == SDLK_d && paddle->getSpeedX() > 0) {
			paddle->setSpeedX(0);
		}
		
		if (keyPressed == SDLK_RETURN) {
			gameStatus->ballFrozenCount = 0;
		}

		if (keyPressed == SDLK_ESCAPE || keyPressed == SDLK_q) {
			return true;
		}
	}
	
	if (e.type == SDL_KEYDOWN) {
		SDL_Keycode keyPressed = e.key.keysym.sym;

		if (keyPressed == SDLK_r) {
			if (gameStatus->gameOver) {
				restartGame();
			}
			
		}
		
		if (keyPressed == SDLK_a) {
			paddle->setSpeedX(-PADDLE_SPEED);
		}
		if (keyPressed == SDLK_d) {
			paddle->setSpeedX(PADDLE_SPEED);
		}
		if (keyPressed == SDLK_p) {
			togglePause();
		}
		if (keyPressed == SDLK_i) {
			int newVol = (sfxManager->getMusicVolume()) - (MIX_MAX_VOLUME / 10); //TODO
			SFXManager::instance().setMusicVolume(newVol);
		}
		if (keyPressed == SDLK_o) {
			int newVol = (sfxManager->getMusicVolume()) + (MIX_MAX_VOLUME / 10); //TODO
			SFXManager::instance().setMusicVolume(newVol);
		}
	}

	return false;
}

void BreakoutGame::togglePause() {
	gameStatus->isPaused = !gameStatus->isPaused;
	SFXManager::instance().toggleMusic();
}

void BreakoutGame::handleCollisions() {
	if (ball->isCollidingWithPaddle(paddle)) {
		ball->bounceOffPaddle(paddle);
		SFXManager::instance().playSFX("./resources/bounce.wav");
	}

	int bricksDestroyed = level->handleBallCollisions(ball);
	if (bricksDestroyed > 0) {
		//play sfx
		SFXManager::instance().playSFX("./resources/break.wav");
		//add to score
		gameStatus->score += bricksDestroyed;
	}
}

bool BreakoutGame::getNextLevel() {
	++curLevel;

	if (cp.hasNextLevel(curLevel)) {
		level = cp.getLevel(curLevel);
		ball->resetBall();
		gameStatus->ballFrozenCount = 1;
		return true;
	}
	else {
		return false;
	}
}

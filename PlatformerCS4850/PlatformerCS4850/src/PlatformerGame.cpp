#include <ctime>
#include "../include/PlatformerGame.h"
#include "../include/Level.h"
#include "../include/Enemy.h"
#include "../include/ConfigParser.h"
#include "../include/GameStatus.h"
#include "../include/Rocket.h"
#include "../include/Battery.h"

#include <SDL_ttf.h>
#include <string>

#include <thread>
#include <chrono>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
PlatformerGame::PlatformerGame(int w, int h) :screenWidth(w), screenHeight(h) {
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
		gWindow = SDL_CreateWindow("In the Dark",
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

void PlatformerGame::startGame() {
	// Initialize game elements
	int lives = std::stoi(ConfigParser::instance().getSetting("lives", "3"));
	GameStatus::instance().init(lives);

	uiManager = new UIManager;

	SFXManager::instance().playMusic("./resources/music.wav");

	level = ConfigParser::instance().parseLevel("./resources/level1.txt");
	
	visibilityCircle = new VisibleCircle();
	visibilityCircle->init(this->level->getPlayer());
}


void PlatformerGame::restartGame() {
	curLevel = 0;
	int lives = std::stoi(ConfigParser::instance().getSetting("lives", "3"));
	GameStatus::instance().init(lives);
	GameStatus::instance().playerInvulnCount = -1;
	level = ConfigParser::instance().parseLevel("./resources/level1.txt");
	visibilityCircle->init(this->level->getPlayer());
}

// Proper shutdown and destroy initialized objects
PlatformerGame::~PlatformerGame() {
	delete level;
	delete uiManager;
	ResourceManager::instance().reset();

	// Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	// Destroy window
	SDL_DestroyWindow(gWindow);
	// Point gWindow to NULL to ensure it points to nothing.
	gRenderer = NULL;
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
}

void PlatformerGame::update() {
	level->update();
	level->handlePlayerCollisions();
	visibilityCircle->update();

	SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
	SDL_RenderClear(gRenderer);

	this->checkGameLoss();
}

void PlatformerGame::checkGameLoss() {
	if (GameStatus::instance().health <= 0) {
		GameStatus::instance().state = LOST;
	}
}

// Render - The render function gets called once per loop
void PlatformerGame::render() {
	level->render(getSDLRenderer());
	visibilityCircle->render(getSDLRenderer());
	uiManager->render(getSDLRenderer());

	SDL_RenderPresent(gRenderer);
}

//Loops forever!
void PlatformerGame::play() {
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
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			// User posts an event to quit
			// An example is hitting the "x" in the corner of the window.
			quit = handleKeyboard(e);

			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		GameState state = GameStatus::instance().state;
		if (state == PLAYING) {
			update();
		}

		// Render using OpenGL
		render();
		// Update screen of our specified window
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
SDL_Window* PlatformerGame::getSDLWindow() {
	return gWindow;
}

// Get Pointer to Renderer
SDL_Renderer* PlatformerGame::getSDLRenderer() {
	return gRenderer;
}

bool PlatformerGame::handleKeyboard(SDL_Event e) {
	Player* player = this->level->getPlayer();
	if (e.type == SDL_KEYUP) {
		SDL_Keycode keyPressed = e.key.keysym.sym;


		if (keyPressed == SDLK_a && player->getVelocity().x < 0) {
			Vector3D currentVel = player->getVelocity();
			player->setVelocity(Vector3D(0, currentVel.y, 0));
		}
		if (keyPressed == SDLK_d && player->getVelocity().x > 0) {
			Vector3D currentVel = player->getVelocity();
			player->setVelocity(Vector3D(0, currentVel.y, 0));
		}

		if (keyPressed == SDLK_ESCAPE || keyPressed == SDLK_q) {
			return true;
		}
	}

	if (e.type == SDL_KEYDOWN) {
		SDL_Keycode keyPressed = e.key.keysym.sym;

		if (keyPressed == SDLK_r) {
			if (GameStatus::instance().state == LOST) {
				restartGame();
			}

		}

		if (keyPressed == SDLK_SPACE && !player->isAirborne()) {
			player->jump();
		}

		if (keyPressed == SDLK_a) {
			Vector3D currentVel = player->getVelocity();
			player->setVelocity(Vector3D(-PLAYER_RUNNING_SPEED, currentVel.y, 0));
		}
		if (keyPressed == SDLK_d) {
			Vector3D currentVel = player->getVelocity();
			player->setVelocity(Vector3D(PLAYER_RUNNING_SPEED, currentVel.y, 0));
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

void PlatformerGame::togglePause() {
	GameState state = GameStatus::instance().state;
	if (state != LOST && state != WON) {
		state == PAUSED ? GameStatus::instance().state = PLAYING : GameStatus::instance().state = PAUSED;
	}
	SFXManager::instance().toggleMusic();
}

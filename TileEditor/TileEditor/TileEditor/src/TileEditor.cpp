#include <sstream>
#include <iostream>
#include "../include/TileEditor.h"

TileEditor::TileEditor() { }

TileEditor::~TileEditor() { }

void TileEditor::init() {
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
		gWindow = SDL_CreateWindow("Tile Editor",
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

		if (!success) {
			errorStream << "Failed to initialize!\n";
			std::string errors = errorStream.str();
			std::cout << errors << "\n";
		}
		else {
			std::cout << "No SDL or OpenGL errors Detected\n\n";
		}
	}

	int y = SIDE_BUFFER + (BOTTOM_BUFFER / 2) + TILE_SIZE * NUM_ROWS;

	int xTotal = TILE_SIZE * NUM_COLUMNS;

	buttonOne = new Button(SIDE_BUFFER, y, 100, 20, "Tiles", TILES);
	buttonTwo = new Button(xTotal / 2 - (100/2), y, 100, 20, "Props", PROPS);
	buttonThree = new Button(xTotal - SIDE_BUFFER - (100 / 2), y, 100, 20, "Flags", FLAGS);
}

//Loops forever!
void TileEditor::play() {
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

			// TODO
			currentEditMode = buttonOne->handleEvent(e, currentEditMode);
			currentEditMode = buttonTwo->handleEvent(e, currentEditMode);
			currentEditMode = buttonThree->handleEvent(e, currentEditMode);

			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		update();

		// Render using OpenGL
		render();

		//Update screen of our specified window
		SDL_GL_SwapWindow(gWindow);

		//SDL_Delay(250); //TODO

		// Delay to force 60 FPS
		int diff = SDL_GetTicks() - start;
		//float delay = 1000.0f / (FRAMERATE / numFrames) - diff;
		float delay = 1000.0f / (FRAMERATE - diff);
		if (delay > 0) {
			SDL_Delay(delay);
		}

	}

	//Disable text input
	SDL_StopTextInput();
}

void TileEditor::render() {
	drawGrid();
	buttonOne->render(gRenderer);
	buttonTwo->render(gRenderer);
	buttonThree->render(gRenderer);
	SDL_RenderPresent(gRenderer);
}

void TileEditor::update() {
	SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
	SDL_RenderClear(gRenderer);
}

bool TileEditor::handleKeyboard(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		SDL_Keycode keyPressed = e.key.keysym.sym;

		if (keyPressed == SDLK_ESCAPE || keyPressed == SDLK_RETURN) {
			return true;
		}
	}

	return false;
}

void TileEditor::drawGrid() {
	SDL_SetRenderDrawColor(gRenderer, GRID_COLOR.r, GRID_COLOR.g, 
		GRID_COLOR.b, GRID_COLOR.a);

	// draw vertical lines
	int tempX;
	for (int i = 0; i <= NUM_COLUMNS; i++) {
		tempX = SIDE_BUFFER + i * TILE_SIZE;
		SDL_RenderDrawLine(gRenderer, tempX, SIDE_BUFFER,
			tempX, SIDE_BUFFER + TILE_SIZE*NUM_ROWS);
	}

	// draw horizontal lines
	int tempY;
	for (int i = 0; i <= NUM_ROWS; i++) {
		tempY = SIDE_BUFFER + i * TILE_SIZE;
		SDL_RenderDrawLine(gRenderer, SIDE_BUFFER, tempY,
			SIDE_BUFFER + TILE_SIZE * NUM_COLUMNS, tempY);
	}
}

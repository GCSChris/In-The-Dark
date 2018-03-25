#include "../include/TileEditor.h"

TileEditor::TileEditor() { }

TileEditor::~TileEditor() { 
	delete buttonOne;
	delete buttonTwo;
	delete buttonThree;
	delete buttonFour;
	delete buttonFive;

	delete level;
}

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
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
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

	int xTotal = TILE_SIZE * NUM_COLUMNS + (SIDE_BUFFER * 2);

	int buttonWidth = 100;
	int buttonHeight = 20;
	buttonOne = new Button(SIDE_BUFFER, y, buttonWidth, buttonHeight, "Tiles", EditMode::TILES);
	buttonTwo = new Button(SIDE_BUFFER + buttonWidth + 10, y, buttonWidth, buttonHeight, 
		"Props", EditMode::PROPS);
	buttonThree = new Button(SIDE_BUFFER + 2*buttonWidth + 20, y, buttonWidth, buttonHeight, 
		"Flags", EditMode::FLAGS);
	buttonFour = new SaveLoadButtons(SIDE_BUFFER + NUM_COLUMNS * TILE_SIZE - buttonWidth, y, 
		buttonWidth, buttonHeight, "Load Level", true);
	buttonFive = new SaveLoadButtons(SIDE_BUFFER + NUM_COLUMNS * TILE_SIZE - buttonWidth * 2 - 10, 
		y, buttonWidth, buttonHeight, "Save Level", false);

	level = new Level();
	level->init();

	currentEditMode = EditMode::TILES;

	printf("STARTING AT MODE %i\n", currentEditMode);
}

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
			EditMode buttonOneMode = buttonOne->handleEvent(e, currentEditMode);
			EditMode buttonTwoMode = buttonTwo->handleEvent(e, currentEditMode);
			EditMode buttonThreeMode = buttonThree->handleEvent(e, currentEditMode);
			buttonFour->handleEvent(e, level);
			buttonFive->handleEvent(e, level);

			if (buttonOneMode != currentEditMode) {
				//printf("switching to buttonOneMode, %i", buttonOneMode);
				currentEditMode = buttonOneMode;
				printf("current edit mode is now %i\n", currentEditMode);
			}
			else if (buttonTwoMode != currentEditMode) {
				//printf("switching to buttonTwoMode, %i", buttonTwoMode);
				currentEditMode = buttonTwoMode;
				printf("current edit mode is now %i\n", currentEditMode);
			}
			else if (buttonThreeMode != currentEditMode) {
				//printf("switching to buttonThreeMode, %i", buttonThreeMode);
				currentEditMode = buttonThreeMode;
				printf("current edit mode is now %i\n", currentEditMode);
			}
			
			if (e.type == SDL_MOUSEBUTTONDOWN) {
			// listen for clicks
				if (e.button.button == SDL_BUTTON_LEFT || e.button.button == SDL_BUTTON_RIGHT) {
					printf("click\n");
					int x, y, tileRow, tileColumn;

					//Get the mouse offsets
					x = e.button.x;
					y = e.button.y;

					tileRow = (y - SIDE_BUFFER) / TILE_SIZE;
					tileColumn = (x - SIDE_BUFFER) / TILE_SIZE;

					if (tileRow < NUM_ROWS && tileRow >= 0
						&& tileColumn < NUM_COLUMNS && tileColumn >= 0) {
						
						editTile(tileRow, tileColumn, e.button.button == SDL_BUTTON_LEFT);
					}
				}
			}

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
	renderBg();
	
	renderTiles();
	
	drawGrid();
	
	buttonOne->render(gRenderer, currentEditMode);
	buttonTwo->render(gRenderer, currentEditMode);
	buttonThree->render(gRenderer, currentEditMode);
	buttonFour->render(gRenderer);
	buttonFive->render(gRenderer);

	SDL_RenderPresent(gRenderer);
}

void TileEditor::update() {
	SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 0xFF);
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

void TileEditor::editTile(int tileRow, int tileColumn, bool leftClick) {
	int i;

	int modeInt = (int) currentEditMode;

	switch (currentEditMode) {
		case EditMode::TILES: //tiles
			printf("tiles case\n");
			i = editTileVal(level->getTileAt(tileRow, tileColumn), leftClick);

			level->setTileAt(tileRow, tileColumn, i);

			break;
		case EditMode::PROPS: //PROPS
			printf("props case\n");
			i = editTileVal(level->getPropAt(tileRow, tileColumn), leftClick);

			level->setPropAt(tileRow, tileColumn, i);
			break;
		case EditMode::FLAGS: //FLAGS CASE
			printf("flags case\n");
			i = editTileVal(level->getFlagAt(tileRow, tileColumn), leftClick);

			level->setFlagAt(tileRow, tileColumn, i);
			break;
		default:
			// this should never happen
			printf("default case\n");
			break;
	}

	tilesUpdated = true;
}

int TileEditor::editTileVal(int tileVal, bool leftClick) {
	printf("tile val is %i", tileVal);
	if (leftClick) {
		return tileVal + 1;
	}
	else {
		return tileVal - 1;
	}
}

void TileEditor::renderTiles() {
	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			renderTile(r, c);
		}
	}
}

void TileEditor::renderTile(int r, int c) {
	int x = SIDE_BUFFER + (c * TILE_SIZE);
	int y = SIDE_BUFFER + (r * TILE_SIZE);

	SDL_Rect tileRect = { x, y, TILE_SIZE, TILE_SIZE };

	SDL_Texture* texture = ResourceManager::instance().getTextureFromImage("resources/tiles.png", gRenderer);
	int tileX = level->getTileAt(r, c); // TODO
	SDL_Rect src_rect_tile = { tileX * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };

	SDL_Texture* propTexture = ResourceManager::instance().getTextureFromImage("resources/props.png", gRenderer);
	int propX = level->getPropAt(r, c); //TODO
	SDL_Rect src_rect_prop = { propX * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };

	SDL_Texture* flagTexture = ResourceManager::instance().getTextureFromImage("resources/flags.png", gRenderer);
	int flagX = level->getFlagAt(r, c); //TODO
	SDL_Rect src_rect_flag = { flagX * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };

	SDL_Rect dest_rect = { x, y, TILE_SIZE, TILE_SIZE };
	SDL_RenderCopy(gRenderer, texture, &src_rect_tile, &dest_rect);
	SDL_RenderCopy(gRenderer, propTexture, &src_rect_prop, &dest_rect);
	SDL_RenderCopy(gRenderer, flagTexture, &src_rect_flag, &dest_rect);
}

void TileEditor::renderBg() {
	SDL_Texture* bg = ResourceManager::instance().getTextureFromImage("resources/background.bmp", gRenderer);

	SDL_Rect srcRect = {0, 0, TILE_SIZE * NUM_COLUMNS, TILE_SIZE * NUM_ROWS };
	SDL_Rect destRect = { SIDE_BUFFER, SIDE_BUFFER, TILE_SIZE * NUM_COLUMNS, TILE_SIZE * NUM_ROWS };

	SDL_RenderCopy(gRenderer, bg, &srcRect, &destRect);
}

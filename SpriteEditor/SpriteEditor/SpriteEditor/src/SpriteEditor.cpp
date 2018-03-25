#include <ctime>
#include <string>
#include <thread>
#include <chrono>

#include "../include/SpriteEditor.h"
#include "../include/ResourceManager.h"

SpriteEditor::SpriteEditor() { }

SpriteEditor::~SpriteEditor() { }

/** Smooth 60fps. */
const int FRAMERATE = 60;
const std::string RESOURCES_DIR = "./resources/";

void SpriteEditor::init() {
	configureFromUserInput();
	setNumColumns();
	
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	gWindow = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
		// Center window on user's screen.
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		int width = DM.w;
		int height = DM.h;

		// Create window
		gWindow = SDL_CreateWindow("Sprite Editor",
			(width / 2)- (frameWidth / 2),
			(height / 2) - (frameHeight / 2),
			frameWidth,
			frameHeight,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		// Check if Window did not create.
		if (gWindow == NULL) {
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}
		else {
			// Set up PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}

		// Create a Renderer to draw on
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
}

void SpriteEditor::cleanUp() {
	// Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	// Destroy window
	SDL_DestroyWindow(gWindow);
	// Point gWindow to NULL to ensure it points to nothing.
	gRenderer = NULL;
	gWindow = NULL;
	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void SpriteEditor::configureFromUserInput() {
	std::cout << "What is the name of the sprite sheet (name of the PNG file) you wish to preview?" << std::endl;
	std::cin >> fileName;
	fileName = RESOURCES_DIR + fileName + ".png";

	std::cout << "What is the width of one sprite in the sprite sheet (in pixels)?" << std::endl;
	std::cin >> frameWidth;

	std::cout << "What is the height of one sprite in the sprite sheet (in pixels)?" << std::endl;
	std::cin >> frameHeight;

	std::cout << "What is the total number of frames in your sprite's animation cycle?" << std::endl;
	std::cin >> numFrames;

	std::cout << "Note: Each frame in the spritesheet will be rendered once per second." << std::endl;
	
	std::cout << "Playing your spritesheet! Press the escape key on your keyboard to exit this application." << std::endl;
}

void SpriteEditor::setNumColumns() {
	SDL_Point dimensions = ResourceManager::instance().getIMGDimensions(fileName);
	int width = dimensions.x;
	numColumns = width / frameWidth;
}

void SpriteEditor::update() {
	if (frame >= FRAMERATE) {
		frame = 0;
	}

	if ((frame % (FRAMERATE / numFrames)) == 0) {
		currentFrame++;
	}

	if (currentFrame >= numFrames) {
		currentFrame = 0;
	}
	
	frame++;

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(gRenderer);
}

void SpriteEditor::render() {
	SDL_Texture* texture = ResourceManager::instance().getTextureFromImage(fileName.c_str(), gRenderer);

	int frameRectWidth = (currentFrame % numColumns) * frameWidth;
	int frameRectHeight = (currentFrame / numColumns) * frameHeight;

	SDL_Rect src_rect = { frameRectWidth, frameRectHeight, frameWidth, frameHeight };
	SDL_Rect dest_rect = { 0, 0, frameWidth, frameHeight };

	SDL_RenderCopy(gRenderer, texture, &src_rect, &dest_rect);
	SDL_RenderPresent(gRenderer);
}

void SpriteEditor::run() {
	// If this is quit = 'true' then the program terminates.
	bool quit = false;
	
	SDL_Event e;
	// Enable text input
	SDL_StartTextInput();
	
	// main loop
	while (!quit) {
		Uint32 start = SDL_GetTicks();
		
		while (SDL_PollEvent(&e) != 0) {
			quit = handleKeyboard(e);

			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		update();
		// Render using OpenGL
		render();

		//Update screen of our specified window
		SDL_GL_SwapWindow(getSDLWindow());
		
		// Delay to force the desired framerate
		int diff = SDL_GetTicks() - start;
		float delay = 1000.0f / (FRAMERATE - diff);
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}

	//Disable text input
	SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* SpriteEditor::getSDLWindow() {
	return gWindow;
}

// Get Pointer to Renderer
SDL_Renderer* SpriteEditor::getSDLRenderer() {
	return gRenderer;
}

bool SpriteEditor::handleKeyboard(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		SDL_Keycode keyPressed = e.key.keysym.sym;

		if (keyPressed == SDLK_ESCAPE) {
			return true;
		}
	}

	return false;
}

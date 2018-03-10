#include <ctime>
#include <string>
#include <thread>
#include <chrono>

#include "../include/SpriteEditor.h"

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SpriteEditor::SpriteEditor(int w, int h, int frames) :frameWidth(w), frameHeight(h), numFrames(frames) {
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	gWindow = NULL;
	// Render flag
	//TTF_Init();

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
		//TODO
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		int width = DM.w;
		int height = DM.h;
		//.

		//Create window
		gWindow = SDL_CreateWindow("Sprite Editor",
			(width / 2)- (frameWidth / 2), // wut?
			(height / 2) - (frameHeight / 2), // wut??
			frameWidth,
			frameHeight,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);

		// Check if Window did not create.
		if (gWindow == NULL) {
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}
		else {
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				//TODO gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
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

	start();
}

void SpriteEditor::start() {
	// Initialize game elements
	
	//TODO
}

// Proper shutdown and destroy initialized objects
SpriteEditor::~SpriteEditor() {
	// Destroy Renderer
	SDL_DestroyRenderer(gRenderer);
	//Destroy window
	SDL_DestroyWindow(gWindow);
	// Point gWindow to NULL to ensure it points to nothing.
	gRenderer = NULL;
	gWindow = NULL;
	//Quit SDL subsystems
	IMG_Quit(); //new TODO
	SDL_Quit();
	//TTF_Quit();
	//Mix_Quit();
}

// Update OpenGL
void SpriteEditor::update() {
	static int frame = 0;
	frame++;
	if (frame > (numFrames - 1)) { //TODO 3 NUM OF FRAMES
		frame = 0;
	}

	currentFrame = frame;

	SDL_SetRenderDrawColor(gRenderer, 0x22, 0x22, 0x22, 0xFF);
	SDL_RenderClear(gRenderer);
}

// Render
// The render function gets called once per loop
void SpriteEditor::render() {
	//level->render(getSDLRenderer());

	SDL_Rect fillRect;
	fillRect.x = 0;
	fillRect.y = 500;
	fillRect.w = 100;
	fillRect.h = 200;

	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &fillRect);


	SDL_Surface* image = IMG_Load("test.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, image);

	//RED
	//SDL_Rect src_rect = { 0, 0, 20, 30 };
	//SDL_Rect dest_rect = { 0, 0, 20, 30 };

	//BLUE
	int frameRect = currentFrame * frameWidth;
	printf("%i\n", frameRect);
	SDL_Rect src_rect = { frameRect, 0, frameWidth, frameHeight };
	SDL_Rect dest_rect = { 0, 0, frameWidth, frameHeight };

	//printf("w: %i, h: %i\n", image->w, image->h);
	SDL_RenderCopy(gRenderer, texture, &src_rect, &dest_rect);

	SDL_RenderPresent(gRenderer);
}

//Loops forever!
void SpriteEditor::play() {
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

		update();

		// Render using OpenGL
		render();
		//Update screen of our specified window
		SDL_GL_SwapWindow(getSDLWindow());



		//SDL_Delay(250); //TODO
		
		// Delay to force 60 FPS
		int diff = SDL_GetTicks() - start;
		float delay = 1000.0f / (FRAMERATE / numFrames) - diff;
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

		if (keyPressed == SDLK_ESCAPE || keyPressed == SDLK_RETURN) {
			return true;
		}
	}

	return false;
}

#include "../include/ResourceManager.h"
#include "../include/LocalizationManager.h"
#include "../include/ConfigParser.h"
#include "../include/PlatformerGame.h"
#include "../include/Constants.h"
#undef main

int main() {
	// Create an instance of an object for a SDLGraphicsProgram
	PlatformerGame* game = new PlatformerGame(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Run our program forever
	game->play();
	
	// call destructor and clean up the program.
	delete game;
	
	return 0;
}

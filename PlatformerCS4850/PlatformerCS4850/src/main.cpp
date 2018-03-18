#include "../include/ResourceManager.h"
#include "../include/LocalizationManager.h"
#include "../include/ConfigParser.h"
#include "../include/PlatformerGame.h"
#include "../include/Constants.h"
#undef main

int main() {
	// Load subsytems for Localization and Config
	//ConfigParser::instance().parseGameConfig();
	//LocalizationManager::instance().loadLocalization();

	// Create an instance of an object for a SDLGraphicsProgram
	PlatformerGame game(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Run our program forever
	game.play();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}

#include "../include/ResourceManager.h"
#include "../include/LocalizationManager.h"
#include "../include/ConfigParser.h"
#undef main

int main() {
	// Load subsytems for Localization and Config
	//ConfigParser::instance().parseGameConfig();
	//LocalizationManager::instance().loadLocalization();

	printf("hello\n");
	// Create an instance of an object for a SDLGraphicsProgram
	//BreakoutGame breakout;
	// Run our program forever
	//breakout.play();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}

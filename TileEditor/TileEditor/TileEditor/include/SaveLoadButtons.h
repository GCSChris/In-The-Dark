#ifndef SAVELOADBUTTONS_H
#define SAVELOADBUTTONS_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Parser.h"
#include "Level.h"

/**
* Buttons that control saving and loading the level.
*/
class SaveLoadButtons {
public:
	/**
	* Constructs a new save or load button.
	*/
	SaveLoadButtons(/** the x position */ int x,/** the y position */ int y, 
		/** button width */ int w, /** button height */ int h, 
		/** the display text */ std::string message, /** whether it loads a level */ bool isLoadButton);

	/**
	* Handles the rendering of buttons.
	*/
	void render(/** The renderer */ SDL_Renderer* gRenderer);

	/**
	* Handles mouse click events on the button.
	*/
	void handleEvent(/** The event */ SDL_Event event, 
		/** The level's current state, if it needs to be saved*/ Level* l);

	/**
	* Helper method for rendering text on top of the button.
	*/
	void renderTextHelp(/** The renderer */ SDL_Renderer* gRenderer, 
		/** The text to render */ std::string text, TTF_Font* font, 
		/** The color to render in */SDL_Color color);

private:
	/** Stores the coordinates and dimensions of the button */
	SDL_Rect buttonRect_;

	/** Indicates whether the button is responsible for loading a level (it saves if false) */
	bool isLoadButton_;

	/** The string displayed on the button */
	std::string message_;
};

#endif

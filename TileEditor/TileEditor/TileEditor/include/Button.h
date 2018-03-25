#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include "Constants.h"
#include "ResourceManager.h"

/**
* An interactable GUI button that changes the edit mode in the tile editor.
*/
class Button {
public:

	/**
	* A constructor that makes a new button given z and y coordinates and desired width 
	* and height, message, and edit mode that this button controls.
	*/
	Button(/** The x position of the button */ int x,/** The y position of the button */ int y,
		/** The button width */ int w, /** The button height */ int h, 
		/** The message to be displayed on the button*/ std::string message, 
		/** The edit mode (tile, flag, or prop) that this button controls */ EditMode mode);

	/**
	* Renders the button, indicating the current active edit mode with a contrasting button color.
	*/
	void render(/** The renderer to draw the image */ SDL_Renderer* gRenderer, 
		/** The current edit mode the Tile editor is in */ EditMode currentEditMode);

	/**
	* Checks for mouse clicks and handles clicks on the button. 
	*/
	EditMode handleEvent(/** The event to handle */ SDL_Event event, 
		/** The current mode that the tile editor is in*/ EditMode currentEditMode);

	/**
	* A helper method for rendering the message string on top of the button.
	*/
	void renderTextHelp(/** The renderer to draw the image */ SDL_Renderer* gRenderer, 
		/** The message to render */ std::string text, 
		/** The font to write the message in */ TTF_Font* font, 
		/** The font color */ SDL_Color color);

private:
	/** Stores the coordinates and dimensions of the button */
	SDL_Rect buttonRect_;

	/** Stores the button's display message */
	std::string message_;

	/** Indicates the mode that the button controls */
	EditMode mode_;
};
 
#endif

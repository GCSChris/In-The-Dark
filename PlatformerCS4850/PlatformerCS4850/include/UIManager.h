#ifndef UI_MANAGER__H
#define UI_MANAGER__H

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameStatus.h"

/** A manager for UI Rendering */
class UIManager {
public:
	/** Default Constructor */
	UIManager();

	/** Renders the UI */
	void render(/** The renderer to use */ SDL_Renderer* gRenderer);


private:
	/** Render the paused screen text */
	void renderPauseText(/** The renderer to use */ SDL_Renderer* gRenderer);
	/** Render the game won text */
	void renderWinText(/** The renderer to use */ SDL_Renderer* gRenderer);
	/** Render the game over text */
	void renderLossText(/** The renderer to use */ SDL_Renderer* gRenderer);

	/** A helper method for rendering text */
	void renderTextHelp(/** The renderer to use */ SDL_Renderer* gRenderer,
		/** The text to render */ std::string text,
		/** The font to render text */TTF_Font* font, 
		/** The color of the font */ SDL_Color color,
		/** The upper left x coordinate */int x, 
		/** The upper left y coordinate */int y);

	void announcementTextHelp(/** The renderer to use */ SDL_Renderer* gRenderer,
		/** The text to render */ std::string text,
		/** The font to render text */TTF_Font* font,
		/** The color of the font */ SDL_Color color);
	
	/** The GameStatus to render */
	GameStatus* uiPlayerStatus;
};

#endif

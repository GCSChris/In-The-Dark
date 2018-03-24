#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Constants.h"

class Button {
public:
	Button(SDL_Rect* rect, std::string message, EditMode mode);

	Button(int x, int y, int w, int h, std::string message, EditMode mode);

	void render(SDL_Renderer* gRenderer, EditMode currentEditMode);

	EditMode handleEvent(SDL_Event event, EditMode currentEditMode);

	void renderTextHelp(SDL_Renderer* gRenderer, std::string text, TTF_Font* font, SDL_Color color);

private:
	SDL_Rect* buttonRect_;
	std::string message_;
	EditMode mode_;
};

#endif

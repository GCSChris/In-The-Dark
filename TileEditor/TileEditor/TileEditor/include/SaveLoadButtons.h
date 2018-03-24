#ifndef SAVELOADBUTTONS_H
#define SAVELOADBUTTONS_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Level.h"

class SaveLoadButtons {
public:
	SaveLoadButtons(int x, int y, int w, int h, std::string message, bool isLoadButton);

	void render(SDL_Renderer* gRenderer);

	void handleEvent(SDL_Event event, Level* l);

	void renderTextHelp(SDL_Renderer* gRenderer, std::string text, TTF_Font* font, SDL_Color color);

private:
	SDL_Rect* buttonRect_;
	bool isLoadButton_;
	std::string message_;
};

#endif

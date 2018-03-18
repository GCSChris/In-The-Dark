#include <string>
#include <iostream>

#include "../include/Button.h"
#include "../include/ResourceManager.h"

const std::string DEFAULT_TEXT_FONT_STYLE = "./resources/arial.ttf";
const int DEFAULT_TEXT_FONT_SIZE = 16;
const SDL_Color DEFAULT_TEXT_FONT_COLOR = { 255, 255, 255, 255 };

Button::Button(SDL_Rect* rect, std::string message, EditMode mode) {
	buttonRect_ = rect;
	message_ = message;
	mode_ = mode;
}

Button::Button(int x, int y, int w, int h, std::string message, EditMode mode) {
	SDL_Rect* rect = new SDL_Rect{ x, y, w, h };
	buttonRect_ = rect;
	message_ = message;
	mode_ = mode;
}

EditMode Button::handleEvent(SDL_Event event, EditMode currentEditMode) {
	//If a mouse button was pressed
	int x;
	int y;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		//If the left mouse button was pressed
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			x = event.button.x;
			y = event.button.y;

			//printf("mouse clicked, ");

			//If the mouse is over the button
			if ((x > buttonRect_->x) && (x < buttonRect_->x + buttonRect_->w) &&
				(y > buttonRect_->y) && (y < buttonRect_->y + buttonRect_->h)) {

				switch (mode_) { //TODO
					case TILES:
						std::cout << "tiles button" << std::endl;
						break;
					case PROPS:
						std::cout << "props button" << std::endl;
						break;
					case FLAGS:
						std::cout << "flags button" << std::endl;
						break;
					default:
						std::cout << "ERROR" << std::endl;
				}

				return mode_;

				//TODO do something
				//std::cout << "button " + message_ + " clicked" << std::endl;
			}
		}
		return currentEditMode;
	}
}

void Button::render(SDL_Renderer* gRenderer) {
	SDL_Color rectColor = { 0, 0, 255, 255 };

	SDL_SetRenderDrawColor(gRenderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);
	//printf("%i, %i, %i, %i\n", buttonRect_->x, buttonRect_->y, buttonRect_->w, buttonRect_->h);
	SDL_RenderFillRect(gRenderer, buttonRect_);

	ResourceManager& resourceManager = ResourceManager::instance();
	TTF_Font* font = resourceManager.getFont(DEFAULT_TEXT_FONT_STYLE.c_str(), DEFAULT_TEXT_FONT_SIZE);
	SDL_Color textColor = DEFAULT_TEXT_FONT_COLOR;

	renderTextHelp(gRenderer, message_, font, textColor, buttonRect_->x, buttonRect_->y);
}

void Button::renderTextHelp(SDL_Renderer* gRenderer, std::string text, TTF_Font* font, SDL_Color color, int x, int y) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

	int texW = 0;
	int texH = 0;
	
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect rect = { x, y, texW, texH };

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);
}
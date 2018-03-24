#include <string>
#include <iostream>

#include "../include/Button.h"
#include "../include/ResourceManager.h"
#include "../include/Constants.h"

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
					case EditMode::TILES:
						std::cout << "tiles button" << std::endl;
						break;
					case EditMode::PROPS:
						std::cout << "props button" << std::endl;
						break;
					case EditMode::FLAGS:
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
	}
	return currentEditMode;
}

void Button::render(SDL_Renderer* gRenderer, EditMode currentEditMode) {
	SDL_Color rectColor;

	// Selected button
	if (currentEditMode == mode_) {
		rectColor = { 255, 0, 0, 255 };
	}
	else {
		rectColor = { 0, 0, 255, 255 };
	}

	SDL_SetRenderDrawColor(gRenderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);
	SDL_RenderFillRect(gRenderer, buttonRect_);

	ResourceManager& resourceManager = ResourceManager::instance();
	TTF_Font* font = resourceManager.getFont(DEFAULT_TEXT_FONT_STYLE.c_str(), DEFAULT_TEXT_FONT_SIZE);
	SDL_Color textColor = DEFAULT_TEXT_FONT_COLOR;

	renderTextHelp(gRenderer, message_, font, textColor);
}

void Button::renderTextHelp(SDL_Renderer* gRenderer, std::string text, TTF_Font* font, SDL_Color color) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

	int textW = 0;
	int textH = 0;

	SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);

	// center text on the buttons
	int textX = buttonRect_->x + ((buttonRect_->w - textW) / 2);
	int textY = buttonRect_->y + ((buttonRect_->h - textH) / 2);

	SDL_Rect rect = { textX, textY, textW, textH };

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);
}
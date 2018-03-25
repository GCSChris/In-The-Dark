#include "../include/SaveLoadButtons.h"

SaveLoadButtons::SaveLoadButtons(int x, int y, int w, int h, std::string message, bool isLoadButton) {
	buttonRect_ = { x, y, w, h };
	message_ = message;
	isLoadButton_ = isLoadButton;
}

void SaveLoadButtons::render(SDL_Renderer* gRenderer) {
	SDL_Color rectColor = { 226, 50, 27, 255 };

	SDL_SetRenderDrawColor(gRenderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);
	SDL_RenderFillRect(gRenderer, &buttonRect_);

	ResourceManager& resourceManager = ResourceManager::instance();
	TTF_Font* font = resourceManager.getFont(DEFAULT_TEXT_FONT_STYLE.c_str(), DEFAULT_TEXT_FONT_SIZE);
	SDL_Color textColor = DEFAULT_TEXT_FONT_COLOR;

	renderTextHelp(gRenderer, message_, font, textColor);
}

void SaveLoadButtons::handleEvent(SDL_Event event, Level* l) {
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

			//If the mouse is over the button
			if ((x > buttonRect_.x) && (x < buttonRect_.x + buttonRect_.w) &&
				(y > buttonRect_.y) && (y < buttonRect_.y + buttonRect_.h)) {
				if (isLoadButton_) {
					std::cout << "load\n";
					*l = Parser::instance().loadLevel();
				}
				else {
					std::cout << "save\n";
					Parser::instance().writeLevel(l);
				}
			}
		}
	}
}

void SaveLoadButtons::renderTextHelp(SDL_Renderer* gRenderer, std::string text, TTF_Font* font, 
	SDL_Color color) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

	int textW = 0;
	int textH = 0;

	SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);

	// center text on the buttons
	int textX = buttonRect_.x + ((buttonRect_.w - textW) / 2);
	int textY = buttonRect_.y + ((buttonRect_.h - textH) / 2);

	SDL_Rect rect = { textX, textY, textW, textH };

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);
}

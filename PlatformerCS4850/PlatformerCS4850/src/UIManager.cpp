#include <string>

#include <SDL_ttf.h>

#include "../include/UIManager.h"
#include "../include/ResourceManager.h"
#include "../include/Constants.h"
#include "../include/LocalizationManager.h"
#include "../include/GameStatus.h"

UIManager::UIManager() {}

void UIManager::render(SDL_Renderer* gRenderer) {
	GameState state = GameStatus::instance().state;

	if (state == PAUSED) {
		renderPauseText(gRenderer);
	}
	
	if (state == WON) {
		//you win
		renderWinText(gRenderer);
	}
	if (state == LOST) {
		//you lose
		renderLossText(gRenderer);
	}
}

void UIManager::renderPauseText(SDL_Renderer* gRenderer) {
	ResourceManager& resourceManager = ResourceManager::instance();
	TTF_Font* font = resourceManager.getFont(PAUSE_TEXT_FONT_STYLE.c_str(), PAUSE_TEXT_FONT_SIZE);
	SDL_Color color = PAUSE_TEXT_COLOR;
	std::string text = LocalizationManager::instance().localize(PAUSE_TEXT_STRING);
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	
	int x = (SCREEN_WIDTH - texW) / 2;
	int y = (SCREEN_HEIGHT - texH) / 2;
	SDL_Rect rect = { x, y, texW, texH };

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);
}

void UIManager::renderWinText(SDL_Renderer* gRenderer) {
	ResourceManager& resourceManager = ResourceManager::instance();
	TTF_Font* font = resourceManager.getFont(PAUSE_TEXT_FONT_STYLE.c_str(), WIN_TEXT_FONT_SIZE);
	SDL_Color color = WIN_TEXT_COLOR;
	std::string text = LocalizationManager::instance().localize(WIN_TEXT_STRING);

	announcementTextHelp(gRenderer, text, font, color);
}

void UIManager::renderLossText(SDL_Renderer* gRenderer) {
	ResourceManager& resourceManager = ResourceManager::instance();
	TTF_Font* font = resourceManager.getFont(LOSS_TEXT_FONT_STYLE.c_str(), LOSS_TEXT_FONT_SIZE);
	SDL_Color color = LOSS_TEXT_COLOR;
	std::string text = LocalizationManager::instance().localize(LOSS_TEXT_STRING);

	announcementTextHelp(gRenderer, text, font, color);
}

void UIManager::renderTextHelp(SDL_Renderer* gRenderer, std::string text, TTF_Font* font, SDL_Color color, int x, int y) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect rect = { x, y, texW, texH };

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);
}

void UIManager::announcementTextHelp(SDL_Renderer* gRenderer, std::string text, TTF_Font* font, SDL_Color color) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	int x = (SCREEN_WIDTH - texW) / 2;
	int y = (SCREEN_HEIGHT - texH) / 2;
	SDL_Rect rect = { x, y, texW, texH };

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);
}

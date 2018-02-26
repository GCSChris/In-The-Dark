#include <string>

#include <SDL_ttf.h>

#include "../include/UIManager.h"
#include "../include/ResourceManager.h"
#include "../include/Constants.h"
#include "../include/LocalizationManager.h"

UIManager::UIManager() {}

void UIManager::init(GameStatus* playerStatus) {
	//printf("lives is %i", lives);
	uiPlayerStatus = playerStatus;
}

void UIManager::render(SDL_Renderer* gRenderer) {
	renderLivesText(gRenderer);
	renderScoreText(gRenderer);
	if (uiPlayerStatus->isPaused) {
		renderPauseText(gRenderer);
	}
	if (uiPlayerStatus->gameOver) {
		if (uiPlayerStatus->gameWon) {
			//you win
			renderWinText(gRenderer);
		}
		else {
			//you lose
			renderLossText(gRenderer);
		}
	}
}

void UIManager::renderLivesText(SDL_Renderer* gRenderer) {
	ResourceManager& resourceManager = ResourceManager::instance();
	TTF_Font* font = resourceManager.getFont(LIVES_TEXT_FONT_STYLE.c_str(), LIVES_TEXT_FONT_SIZE);
	SDL_Color color = LIVES_TEXT_COLOR;
	std::string text = LocalizationManager::instance().localize(LIVES_TEXT_STRING) + ": " + std::to_string(uiPlayerStatus->lives);
	
	int x = 10;
	int y = 0;
	renderTextHelp(gRenderer, text, font, color, x, y);
}


void UIManager::renderScoreText(SDL_Renderer* gRenderer) {
	ResourceManager& resourceManager = ResourceManager::instance();
	TTF_Font* font = resourceManager.getFont(SCORE_TEXT_FONT_STYLE.c_str(), SCORE_TEXT_FONT_SIZE);
	SDL_Color color = SCORE_TEXT_COLOR;
	std::string text = LocalizationManager::instance().localize(SCORE_TEXT_STRING) + ": " + std::to_string(uiPlayerStatus->score);
	 
	int x = SCREEN_WIDTH;
	int y = 0;
	renderTextHelp(gRenderer, text, font, color, x, y);
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

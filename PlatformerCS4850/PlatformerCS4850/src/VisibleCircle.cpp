#include "../include/VisibleCircle.h"
#include "../include/ResourceManager.h"
#include "../include/GameStatus.h"
#include <iostream>

void VisibleCircle::init(Player* player) {
	this->player = player;
}

void VisibleCircle::update() {
	// TODO fancy interpolation
	float curScale = this->scale;
	this->scale = GameStatus::instance().health;
	int size = curScale * VISIBLE_CIRCLE_MIN_SIZE;
	this->surface = ResourceManager::instance().getScaledSurface(VISIBLE_CIRCLE_SPRITE, size, size);
}

void VisibleCircle::render(SDL_Renderer* r) {
	int centerX = this->player->getX() + (this->player->getWidth() / 2);
	int centerY = this->player->getY() + (this->player->getHeight() / 2);

	int size = VISIBLE_CIRCLE_MIN_SIZE * this->scale;

	int x = centerX - (size / 2);
	int y = centerY - (size / 2);

	if (this->surface == nullptr) {
		this->surface = ResourceManager::instance().getScaledSurface(VISIBLE_CIRCLE_SPRITE, size, size);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(r, this->surface);

	SDL_Rect src = { 0, 0, size, size };
	SDL_Rect dest = { x, y, size, size };

	this->renderBlackout(r, &dest);
	SDL_RenderCopy(r, texture, &src, &dest);
}

void VisibleCircle::renderBlackout(SDL_Renderer* r, SDL_Rect* circleRect) {
	SDL_Rect above = { 0, 0, SCREEN_WIDTH, circleRect->y };
	SDL_Rect below = { 0, circleRect->y + circleRect->h, SCREEN_WIDTH, SCREEN_HEIGHT - (circleRect->y + circleRect->h) };
	SDL_Rect left = { 0, 0, circleRect->x, SCREEN_HEIGHT };
	SDL_Rect right = { circleRect->x + circleRect->w, 0, SCREEN_WIDTH - (circleRect->x + circleRect->w), SCREEN_HEIGHT };

	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
	SDL_RenderFillRect(r, &above);
	SDL_RenderFillRect(r, &below);
	SDL_RenderFillRect(r, &left);
	SDL_RenderFillRect(r, &right);
}
#include "../include/Rocket.h"
#include "../include/GameStatus.h"

void Rocket::render(SDL_Renderer* ren) {
	// TODO
	SDL_Rect fillRect;
	fillRect.x = x;
	fillRect.y = y;
	fillRect.w = w;
	fillRect.h = h;

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderFillRect(ren, &fillRect);
}

void Rocket::handlePlayerCollision() {
	printf("rocket collide!\n");
	GameStatus::instance().state = WON;
}
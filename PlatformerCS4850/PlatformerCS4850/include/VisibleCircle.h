#ifndef VISIBLECIRCLE_H
#define VISIBLECIRCLE_H

#include "Player.h"

class VisibleCircle {
public:
	void init(Player* player);
	void update();
	void render(SDL_Renderer* r);

private:
	void renderBlackout(SDL_Renderer* r, SDL_Rect* circleRect);

	Player* player;
	SDL_Surface* surface;
	float scale = 1;
};

#endif
#ifndef WIN_TILE_H
#define WIN_TILE_H

#include <string>

#include "GameObject.h"
#include "Tile.h"
#include "SpriteSheet.h"
#include "Enums.h"

class Rocket : public GameObject {
public:
	//void init(int x, int y, int w, int h);
	//void update();
	void render(SDL_Renderer* ren);

	void handlePlayerCollision();

private:
	//SpriteSheet * spriteSheet;
	//Direction direction;
};

#endif
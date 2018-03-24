#ifndef BATTERY_H
#define BATTERY_H

#include <string>

#include "GameObject.h"
#include "Tile.h"
#include "SpriteSheet.h"
#include "Enums.h"

class Battery : public GameObject {
public:
	void init(int _x, int _y, int _w, int _h, std::string fileName);
	void render(SDL_Renderer* ren);
	void handlePlayerCollision();

private:
	std::string name;
	SDL_Texture* texture;
	bool used = false;
};

#endif
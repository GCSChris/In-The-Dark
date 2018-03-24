#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "GameObject.h"
#include "Tile.h"
#include "SpriteSheet.h"
#include "Enums.h"

class Player : public GameObject{
public:
	void init(/** The upper left corner x coordinate */ int _x,
		/** The upper left corner y coordinate */ int _y,
		int numFrames,
		std::string spriteSheetFileName, 
		Direction dir = Direction::RIGHT);
	void update();
	void render(SDL_Renderer* ren);
	void preventCollision(GameObject* obj);
	void jump();
	bool isAirborne();

private:
	void capSpeed();

	bool is_airborne = true;
	
	SpriteSheet* spriteSheet;
	Direction direction;
};

#endif
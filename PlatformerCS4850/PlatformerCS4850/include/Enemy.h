#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "GameObject.h"
#include "Tile.h"
#include "SpriteSheet.h"
#include "Enums.h"

class Enemy : public GameObject {
public:
	/** Initializes an Enemy */
	void init(/** The upper left corner x coordinate */ int x,
		/** The upper left corner y coordinate */ int y,
		/** The width of the Enemy */ int w,
		/** The height of the Enemy */ int h,
		/** The name of the sprite sheet */std::string spriteSheetFileName,
		/** The facing direction. Default right */Direction dir = Direction::RIGHT);	
	/** Updates this Enemy. Called once a frame */
	void update();
	/** Renders this enemy */
	void render(/** The renderer to use */SDL_Renderer* ren);
	/** Prevents collision with the given Game Object*/
	void preventCollision(/** The game object to prevent collision with */ GameObject* obj);
	/** What to do when colliding with a player */
	void handlePlayerCollision();

private:
	/** The SpriteSheet to use to render this Enemy */
	SpriteSheet* spriteSheet;
	/** The facing direction of this Enemy */
	Direction direction;
};

#endif
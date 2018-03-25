#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "GameObject.h"
#include "Tile.h"
#include "SpriteSheet.h"
#include "Enums.h"

class Player : public GameObject{
public:
	/** Initializes a player */
	void init(/** The upper left corner x coordinate */ int _x,
		/** The upper left corner y coordinate */ int _y,
		/** The name of the sprite sheet */std::string spriteSheetFileName, 
		/** The facing direction. Default right */Direction dir = Direction::RIGHT);
	
	/** Updates the player. Should be called once a frame */
	void update();

	/** Renders the player */
	void render(/** The rendered to use */SDL_Renderer* ren);

	/** Prevents a collision with the given GameObject.
	 *  This is achieved by moving the player in the opposite direction
	 *  of their velocity until a collision no longer occurs
	 */
	void preventCollision(/** The GameObject to avoid collision with */GameObject* obj);

	/** Makes the player jump */
	void jump();

	/** Returns if the player is airborne or not */
	bool isAirborne();

private:
	/** Caps the players speed, making sure it is inside bounds */
	void capSpeed();

	/** Whether or not the player is in the air*/
	bool is_airborne = true;
	/** The SpriteSheet to use for animation and rendering*/
	SpriteSheet* spriteSheet;
	/** The facing direction of the Player*/
	Direction direction;
};

#endif
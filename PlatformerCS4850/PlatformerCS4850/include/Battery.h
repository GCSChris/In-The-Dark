#ifndef BATTERY_H
#define BATTERY_H

#include <string>

#include "GameObject.h"
#include "Tile.h"
#include "SpriteSheet.h"
#include "Enums.h"

class Battery : public GameObject {
public:
	/** Initiliazes the Battery */
	void init(/** The upper left corner x coordinate */ int _x,
		/** The upper left corner y coordinate */ int _y,
		/** The width */ int _w,
		/** The height */ int _h, 
		/** The filename for the sprite */std::string fileName);

	/** Render this Battery */
	void render(/** The renderer to use */SDL_Renderer* ren);
	
	/** Handle this object when colliding with a player*/
	void handlePlayerCollision();

private:
	/** The filename for this Battery's sprite*/
	std::string name;
	/** The SDL_Texture to render with */
	SDL_Texture* texture;
	/** Whether or not this Battery has been picked up*/
	bool used = false;
};

#endif
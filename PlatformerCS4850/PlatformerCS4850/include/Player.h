#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Tile.h"

class Player : public GameObject{
public:
	void update();
	void render(SDL_Renderer* ren);
	void preventCollision(GameObject* obj);
	void jump();
	bool isAirborne();

private:
	void capSpeed();

	bool is_airborne = true;
	SDL_Texture * current_sprite;
};

#endif
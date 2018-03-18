#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : protected GameObject {
public:
	void render(SDL_Renderer* ren);
private:

};

#endif
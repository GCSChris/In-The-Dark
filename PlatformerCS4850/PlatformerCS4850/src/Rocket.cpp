#include "../include/Rocket.h"
#include "../include/GameStatus.h"
#include "../include/ResourceManager.h"

void Rocket::init(int _x,int _y, int _w, int _h, std::string fileName) {
	GameObject::init(_x, _y, _w, _h);
	name = fileName;
}

void Rocket::render(SDL_Renderer* ren) {
	if (texture == nullptr) {
		texture = ResourceManager::instance().getTexture(name.c_str(), ren);
	}
	
	SDL_Rect dest = { x, y, w, h };
	SDL_RenderCopy(ren, texture, NULL, &dest);
}

void Rocket::handlePlayerCollision() {
	GameStatus::instance().state = WON;
}
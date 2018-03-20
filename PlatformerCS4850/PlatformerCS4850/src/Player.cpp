#include "../include/Player.h"
#include "../include/ResourceManager.h"
#include <iostream>

void Player::update() {
	this->velocity.y += GRAVITY;

	this->capSpeed();
	this->x += this->velocity.x;
	this->y += this->velocity.y;

	if (this->x < 0) {
		this->x = 0;
	}
	else if (this->x + this->w > SCREEN_WIDTH) {
		this->x = SCREEN_WIDTH - this->w;
	}
}

void Player::applyForce(Vector3D force) {
	GameObject::applyForce(force);
}

void Player::render(SDL_Renderer* r) {
	if (this->current_sprite == nullptr) {
		this->current_sprite = ResourceManager::instance().getTexture("./resources/PixelTigerBase_16x32.bmp", r);
	}
	SDL_Rect src = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_Rect dest = { this->x, this->y, PLAYER_WIDTH, PLAYER_HEIGHT };

	SDL_RenderCopy(r, current_sprite, &src, &dest);
}

void Player::preventCollision(Tile* tile) {
	SDL_Rect* intersect = new SDL_Rect();
	/*
	SDL_Rect* groundingRect = new SDL_Rect();
	groundingRect->x = this->x;
	groundingRect->y = this->y + this->h + -1;
	groundingRect->w = this->w;
	groundingRect->h = 1;
	*/

	SDL_IntersectRect(this->getRect(), tile->getRect(), intersect);
	if (intersect->w < 0 || intersect->h < 0) {
		return;
	}

	// remove in the y direction if moving in y direction
	if (this->velocity.y != 0 && intersect->h < TILE_SIZE) {
		this->velocity.y < 0 ? this->y += intersect->h : this->y -= intersect->h;
		this->is_airborne = this->y + this->h > tile->getY();
		this->velocity.y = 0;
		//std::cout << "Moving out vertically" << std::endl;
	} else if (intersect->w < PLAYER_WIDTH && this->velocity.x != 0) {
		//std::cout << "Moving out horizontally" << std::endl;
		this->velocity.x < 0 ? this->x += intersect->w : this->x -= intersect->w;
	}
}

void Player::capSpeed() {
	if (this->velocity.y > PLAYER_FALLING_SPEED_CAP) {
		this->velocity.y = PLAYER_FALLING_SPEED_CAP;
	}
}

void Player::jump() {
	this->velocity.y = 0;
	this->is_airborne = true;
	applyForce(Vector3D(0, -PLAYER_JUMP_FORCE, 0));
}

bool Player::isAirborne() {
	return is_airborne;
}
#include "../include/Player.h"
#include "../include/ResourceManager.h"

#include "../include/PlatformerGame.h"
#include <iostream>

void Player::init(int x, int y, int numFrames, std::string spriteSheetFileName, Direction dir) {
	spriteSheet = new SpriteSheet();
	GameObject::init(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, true);
	direction = dir;
	spriteSheet->init(numFrames, spriteSheetFileName);
}

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

	if (this->velocity.x > 0) {
		this->direction = Direction::RIGHT;
	}
	else if (this->velocity.x < 0) {
		this->direction = Direction::LEFT;
	}
	spriteSheet->update(this->direction);
}

void Player::render(SDL_Renderer* r) {
	spriteSheet->render(r, this->x, this->y);
}

void Player::preventCollision(GameObject* obj) {
	SDL_Rect* intersect = new SDL_Rect();

	SDL_IntersectRect(this->getRect(), obj->getRect(), intersect);
	if (intersect->w < 0 || intersect->h < 0) {
		return;
	}

	// remove in the y direction if moving in y direction
	if (this->velocity.y != 0 && intersect->h < TILE_SIZE) {
		this->velocity.y < 0 ? this->y += intersect->h : this->y -= intersect->h;
		this->is_airborne = this->y + this->h > obj->getY();
		this->velocity.y = 0;
	} else if (intersect->w < PLAYER_WIDTH && this->velocity.x != 0) {
		this->velocity.x < 0 ? this->x += intersect->w : this->x -= intersect->w;
		this->velocity.x = 0;
	}
}

void Player::capSpeed() {
	if (this->velocity.y > TERMINAL_Y_VELOCITY) {
		this->velocity.y = TERMINAL_Y_VELOCITY;
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
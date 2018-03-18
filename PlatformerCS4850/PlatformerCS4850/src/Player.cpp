#include "../include/Player.h"
#include "../include/ResourceManager.h"

void Player::update() {
	this->capSpeed();
	this->x += this->velocity.x;
	if (this->x < 0) {
		this->x = 0;
	}
	else if (this->x + this->w > SCREEN_WIDTH) {
		this->x = SCREEN_WIDTH - this->w;
	}

	if (is_airborne) {
		this->y += this->velocity.y;
	}
}

void Player::applyForce(Vector3D force) {
	GameObject::applyForce(force);
	if (force.y > 0) {
		this->is_airborne = true;
	}
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
	Vector3D backup = -Normalize(velocity);
	
	while (this->isCollidingWithObject(tile)) {
		this->x += backup.x;
		this->y += backup.y;
	}

	this->is_airborne = false;
	this->setVelocity(Vector3D(this->velocity.x, 0, 0));
}

void Player::capSpeed() {
	if (this->velocity.y > PLAYER_FALLING_SPEED_CAP) {
		this->velocity.y = PLAYER_FALLING_SPEED_CAP;
	}
}
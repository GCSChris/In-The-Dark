#include "../include/Enemy.h"
#include "../include/ResourceManager.h"
#include "../include/GameStatus.h"
#include <iostream>

void Enemy::init(int x, int y, int w, int h, std::string spriteSheetFileName, Direction dir) {
	spriteSheet = new SpriteSheet();
	GameObject::init(x, y, w, h, true); 
	direction = dir;
	spriteSheet->init(spriteSheetFileName, ENEMY_WIDTH, ENEMY_HEIGHT);

	this->velocity = Vector3D(ENEMY_RUNNING_SPEED, 0, 0);
}

void Enemy::update() {
	this->velocity.y += GRAVITY;

	if (this->velocity.y > TERMINAL_Y_VELOCITY) {
		this->velocity.y = TERMINAL_Y_VELOCITY;
	}

	this->x += this->velocity.x;
	this->y += this->velocity.y;

	if (this->x < 0) {
		this->x = 0;
		this->velocity.x = -1 * this->velocity.x;
	}
	else if (this->x + this->w > SCREEN_WIDTH) {
		this->x = SCREEN_WIDTH - this->w;
		this->velocity.x = -1 * this->velocity.x;
	}

	if (this->velocity.x > 0) {
		this->direction = Direction::LEFT;
	}
	else if (this->velocity.x < 0) {
		this->direction = Direction::RIGHT;
	}
	spriteSheet->update(this->direction);
}

void Enemy::render(SDL_Renderer* r) {
	spriteSheet->render(r, this->x, this->y, ENEMY_WIDTH, ENEMY_HEIGHT);
}

void Enemy::preventCollision(GameObject* obj) {
	SDL_Rect* intersect = new SDL_Rect();

	SDL_IntersectRect(this->getRect(), obj->getRect(), intersect);
	if (intersect->w < 0 || intersect->h < 0) {
		return;
	}

	// remove in the y direction if moving in y direction
	if (this->velocity.y != 0 && intersect->h < TILE_SIZE) {
		this->velocity.y < 0 ? this->y += intersect->h : this->y -= intersect->h;
		this->velocity.y = 0;
	}
	else if (intersect->w < PLAYER_WIDTH && this->velocity.x != 0) {
		this->velocity.x < 0 ? this->x += intersect->w : this->x -= intersect->w;
		this->velocity.x = -1 * this->velocity.x;
	}
}

void Enemy::handlePlayerCollision() {
	GameStatus* gameStatus = &GameStatus::instance();
	if (gameStatus->playerInvulnCount < 0) {
		// Player is vulnerable
		gameStatus->playerInvulnCount = 0;
		gameStatus->health -= 1;
		// TODO maybe play a sound?
	}
}

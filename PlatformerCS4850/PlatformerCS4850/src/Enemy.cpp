#include "../include/Enemy.h"
#include "../include/ResourceManager.h"

void Enemy::init(int x, int y, int w, int h, const char* sprite_sheet) {
	GameObject::init(x, y, w, h, true);
	this->sprite_sheet = sprite_sheet;
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
}

void Enemy::render(SDL_Renderer* r) {
	if (this->current_sprite == nullptr) {
		this->current_sprite = ResourceManager::instance().getTexture(this->sprite_sheet, r);
	}
	SDL_Rect src = { 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT };
	SDL_Rect dest = { this->x, this->y, ENEMY_WIDTH, ENEMY_HEIGHT };

	SDL_RenderCopy(r, current_sprite, &src, &dest);
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

#include "../include/GameObject.h"
#include <stdlib.h>

#undef main

GameObject::GameObject() {}

void GameObject::init(int _x, int _y, int _w, int _h, bool _collide) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	velocity = Vector3D(0, 0, 0);
	collideable = _collide;
}

void GameObject::update() {
	this->x += this->velocity.x;
	this->y += this->velocity.y;
}

void GameObject::applyForce(Vector3D force) {
	this->velocity += force;
}

void GameObject::render(SDL_Renderer* gRenderer) {
	SDL_Rect fillRect;
	fillRect.x = x;
	fillRect.y = y;
	fillRect.w = w;
	fillRect.h = h;

	SDL_SetRenderDrawColor(gRenderer, 0, 60, 0, 255);
	SDL_RenderFillRect(gRenderer, &fillRect);
}
 
void GameObject::preventCollision(GameObject* obj) {
	// Do nothing
}

bool GameObject::isCollidingWithObject(GameObject* other) {
	if (!(this->collideable && other->isCollideable())) {
		return false;
	}
	
	float thisLeft = this->x;
	float thisRight = this->x + this->w;
	float thisTop = this->y;
	float thisBottom = this->y + this->h;
	float otherLeft = other->x;
	float otherRight = other->x + other->w;
	float otherTop = other->y;
	float otherBottom = other->y + other->h;

	// Separating Axis test learned from LazyFoo: http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
	if (thisBottom <= otherTop) {
		return false;
	}
	else if (thisTop >= otherBottom) {
		return false;
	}
	else if (thisRight <= otherLeft) {
		return false;
	}
	else if (thisLeft >= otherRight) {
		return false;
	}
	
	return true;
}

int GameObject::getX() {
	return x;
}

int GameObject::getY() {
	return y;
}

int GameObject::getWidth() {
	return w;
}

int GameObject::getHeight() {
	return h;
}

bool GameObject::isCollideable() {
	return this->collideable;
}

void GameObject::setVelocity(Vector3D vel) {
	this->velocity = vel;
}

Vector3D GameObject::getVelocity() {
	return velocity;
}

SDL_Rect* GameObject::getRect() {
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return rect;
}
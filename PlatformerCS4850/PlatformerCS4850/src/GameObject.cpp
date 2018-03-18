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

	SDL_SetRenderDrawColor(gRenderer, 165, 42, 42, 255);
	SDL_RenderFillRect(gRenderer, &fillRect);
}

bool GameObject::isCollidingWithObject(GameObject* other) {
	if (!(this->collideable && other->collideable)) {
		return false;
	}
	return (this->isRightEdgeInBounds(other) || this->isLeftEdgeInBounds(other)) 
			&& (this->isTopEdgeInBounds(other) || this->isBottomEdgeInBounds(other));
}

bool GameObject::isRightEdgeInBounds(GameObject* other) {
	return ((x + w )< (other->x + other->w) && ((x + w) > other->x));
}

bool GameObject::isLeftEdgeInBounds(GameObject* other) {
	return (x < (other->x + other->w) && (x > other->x));
}

bool GameObject::isTopEdgeInBounds(GameObject* other) {
	return (y < (other->y + other->h) && (y > other->y));
}

bool GameObject::isBottomEdgeInBounds(GameObject* other) {
	return ((y + h)< (other->y + other->h) && ((y + h) > other->y));
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
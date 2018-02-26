#include "../include/Rectangle.h"
#include <stdlib.h>

#undef main

Rectangle::Rectangle() {}

void Rectangle::init(int _x, int _y, int _w, int _h, SDL_Color _color) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	color = _color;
}

void Rectangle::render(SDL_Renderer* gRenderer) {
	SDL_Rect fillRect;
	fillRect.x = x;
	fillRect.y = y;
	fillRect.w = w;
	fillRect.h = h;

	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(gRenderer, &fillRect);

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(gRenderer, &fillRect);
}

bool Rectangle::isCollidingWithRect(Rectangle* other) {
	return (this->isRightEdgeInBounds(other) || this->isLeftEdgeInBounds(other)) 
			&& (this->isTopEdgeInBounds(other) || this->isBottomEdgeInBounds(other));
}

bool Rectangle::isRightEdgeInBounds(Rectangle* other) {
	return ((x + w )< (other->x + other->w) && ((x + w) > other->x));
}

bool Rectangle::isLeftEdgeInBounds(Rectangle* other) {
	return (x < (other->x + other->w) && (x > other->x));
}


bool Rectangle::isTopEdgeInBounds(Rectangle* other) {
	return (y < (other->y + other->h) && (y > other->y));
}

bool Rectangle::isBottomEdgeInBounds(Rectangle* other) {
	return ((y + h)< (other->y + other->h) && ((y + h) > other->y));
}

int Rectangle::getX() {
	return x;
}

int Rectangle::getY() {
	return y;
}

int Rectangle::getWidth() {
	return w;
}

int Rectangle::getHeight() {
	return h;
}
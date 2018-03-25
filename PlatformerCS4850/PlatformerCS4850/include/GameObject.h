#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <stdbool.h>
#include "Constants.h"
#include "TinyMath.h"

/**
	Represents a 2D GameObject in the X-Y plane.
 */
class GameObject {
public:
	/** Default constructor for a GameObject */
	GameObject();

	/** Initializes a GameObject. */
	void init(/** The upper left corner x coordinate */ int _x,
		/** The upper left corner y coordinate */ int _y,
		/** The width */ int _w,
		/** The height */ int _h,
		/** If this GameObject can be collided with*/ bool _collide = true);

	/** Updates this game object. Called once per frame */
	virtual void update();

	/** Apply a force to this GameObject */
	void applyForce(Vector3D force);

	/** Renders a GameObject */ 
	virtual void render(/** The renderer to use */ SDL_Renderer* gRenderer);

	/** Prevents a collision with another game object. Must be over written to be used */
	virtual void preventCollision(GameObject* other);

	/** What to do when colliding with a player. Does nothing by default. */
	virtual void handlePlayerCollision();

	/** Returns if this GameObject is overlapping with the other GameObject */
	bool isCollidingWithObject(/** The other GameObject */ GameObject* other);

	/** Returns the upper left x coordinate */
	int getX();
	/** Returns the upper left y coordinate */
	int getY();
	/** Returns the width */
	int getWidth();
	/** Returns the height */
	int getHeight();
	/** Sets the velocity */
	void setVelocity(Vector3D vel);
	/** Whether or not this GameObject is collideable */
	bool isCollideable();
	/** Returns the velocity */
	Vector3D getVelocity();
	/** Returns an SDL_Rect for the bounds of this Rectangle */
	SDL_Rect* getRect();

protected:
	/** The upper left x coordinate */
	float x;
	/** The upper left y coordinate */
	float y;
	/** The width of the GameObject */
	int w;
	/** The height of the GameObject */
	int h;
	/** The current velocity of the GameObject */
	Vector3D velocity;
	/** whether this game object handles collisions */
	bool collideable = true;
};

#endif

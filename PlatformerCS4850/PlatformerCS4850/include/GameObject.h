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
		/** The height */ int _h);

	/** Updates this game object. Called once per frame */
	void update();

	/** Apply a force to this GameObject */
	void applyForce(Vector3D force);

	/** Renders a GameObject */ 
	void render(/** The renderer to use */ SDL_Renderer* gRenderer);

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

protected:
	/** If the right edge of this GameObject is within the x-bound of the other GameObject*/
	bool isRightEdgeInBounds(/** The other GameObject */ GameObject* other);
	/** If the left edge of this GameObject is within the x-bound of the other GameObject*/
	bool isLeftEdgeInBounds(/** The other GameObject */ GameObject* other);
	/** If the top edge of this GameObject is within the x-bound of the other GameObject*/
	bool isTopEdgeInBounds(/** The other GameObject */ GameObject* other);
	/** If the bottom edge of this GameObject is within the x-bound of the other GameObject*/
	bool isBottomEdgeInBounds(/** The other GameObject */ GameObject* other);

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
};

#endif

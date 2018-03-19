#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL.h>
#include <stdbool.h>
#include "Constants.h"

/**
	Represents a 2D rectangle in the X-Y plane.
 */
class Rectangle {
public:
	/** Default constructor for a Rectangle */
	Rectangle();

	/** Initializes a Rectangle. */
	void init(/** The upper left corner x coordinate */ int _x,
		/** The upper left corner y coordinate */ int _y,
		/** The width */ int _w,
		/** The height */ int _h,
		/** The color to render this Rectangle */ SDL_Color _color);

	/** Renders a Rectangle */ 
	void render(/** The renderer to use */ SDL_Renderer* gRenderer);

	/** Returns if this Rectangle is overlapping with the other Rectangle */
	bool isCollidingWithRect(/** The other Rectangle */ Rectangle* other);

	/** Returns the upper left x coordinate */
	int getX();
	/** Returns the upper left y coordinate */
	int getY();
	/** Returns the width */
	int getWidth();
	/** Returns the height */
	int getHeight();

protected:
	/** If the right edge of this Rectangle is within the x-bound of the other Rectangle*/
	bool isRightEdgeInBounds(/** The other rectangle */ Rectangle* other);
	/** If the left edge of this Rectangle is within the x-bound of the other Rectangle*/
	bool isLeftEdgeInBounds(/** The other rectangle */ Rectangle* other);
	/** If the top edge of this Rectangle is within the x-bound of the other Rectangle*/
	bool isTopEdgeInBounds(/** The other rectangle */ Rectangle* other);
	/** If the bottom edge of this Rectangle is within the x-bound of the other Rectangle*/
	bool isBottomEdgeInBounds(/** The other rectangle */ Rectangle* other);

	/** The upper left x coordinate */
	int x;
	/** The upper left y coordinate */
	int y;
	/** The width of the Rectangle */
	int w;
	/** The height of the Rectangle */
	int h;
	/** The color of the Rectangle */
	SDL_Color color;
	/** Whether or not this Rectangle can be collided with */
	bool collideable = true;
};

#endif

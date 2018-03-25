#ifndef VISIBLECIRCLE_H
#define VISIBLECIRCLE_H

#include "Player.h"

class VisibleCircle {
public:
	/** Initializes the VisibleCircle*/
	void init(/** The player to follow */Player* player);
	/** Update is called once a frame */
	void update();
	/** Render this visible circle */
	void render(/** The renderer to use */SDL_Renderer* r);

private:
	/** Render blackout bars */
	void renderBlackout(/** The renderer to use */ SDL_Renderer* r,
		/** The rectangle to leave uncovered */ SDL_Rect* circleRect);

	/** The player to center the circle on */
	Player* player;
	/** The surface to draw with */
	SDL_Texture* texture;
	/** The scale of the surface used*/
	int scale = 1;
};

#endif
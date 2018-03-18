#include "Rectangle.h";
#include <string.h>

class Tile : public Rectangle {
public:
	/** Initializes this Tile */
	void init(int x, int y, int w, int h, std::string spriteSheet, int tileIdx, bool collideable);
	/** Renders this Tile */
	void render();

protected:
	/** The SpriteSheet to use for rendering */
	std::string spriteSheet;
	/** The index of the tile to render in the sprite sheet */
	int tileIdx;
};
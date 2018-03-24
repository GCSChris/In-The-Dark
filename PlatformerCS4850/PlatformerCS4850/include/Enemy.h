#include <string>

#include "GameObject.h"
#include "Tile.h"
#include "SpriteSheet.h"
#include "Enums.h"

class Enemy : public GameObject {
public:
	void init(int x, int y, int w, int h, int numFrames, std::string spriteSheetFileName, Direction dir = Direction::LEFT);
	void update();
	void render(SDL_Renderer* ren);
	void preventCollision(GameObject* obj);
	void handlePlayerCollision();

private:
	SpriteSheet* spriteSheet;
	Direction direction;
};
#include "GameObject.h"
#include "Tile.h"

class Enemy : public GameObject {
public:
	void init(int x, int y, int w, int h, const char* sprite_sheet);
	void update();
	void render(SDL_Renderer* ren);
	void preventCollision(GameObject* obj);
private:
	const char* sprite_sheet;
	SDL_Texture* current_sprite;
};
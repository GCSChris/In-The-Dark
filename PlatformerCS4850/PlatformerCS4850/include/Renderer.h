#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <string>
#include <map>

/** A Renderer singleton class */
class Renderer {
public:
	/** Returns the instance of the Renderer */
	static Renderer& instance() {
		if (inst_ == NULL) {
			inst_ = new Renderer();
		}
		return *inst_;
	}

	void renderTexture(SDL_Renderer* rend, SDL_Texture* texture, SDL_Rect src_rect, SDL_Rect dest_rect) {
		SDL_RenderCopy(rend, texture, &src_rect, &dest_rect);
	}

private:
	/** Private constructor */
	Renderer() {}

	/** Private destructor */
	~Renderer() {}

	/** The singleton instance */
	static Renderer* inst_;
};

#endif
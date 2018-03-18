#ifndef RESOURCEMANGER_H
#define RESOURCEMANGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

/** A ResourceManager singleton class */
class ResourceManager {
public:
	/** Returns the instance of the ResourceManager */
	static ResourceManager& instance() {
		if (inst_ == NULL) {
			inst_ = new ResourceManager();
		}
		return *inst_;
	}

	/** Returns a SDL_Texture */
	SDL_Texture* getTexture(/** The string pointing to the resource */const char* resource,
		/** The SDL_Renderer to render the Texture with */ SDL_Renderer* ren) {
		if (textures_.count(resource) > 0) {
			return textures_[resource];
		}

		SDL_Surface* spriteSheet = SDL_LoadBMP(resource);

		if (spriteSheet == NULL) {
			SDL_Log("Failed to allocate surface");
		}
		else {
			SDL_Log("Allocated a bunch of memory to create identical game character");
			// Create a texture from our surface
			// Textures run faster and take advantage of hardware acceleration
			SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 4, 255, 17));
			SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
			textures_.insert(std::pair<const char*, SDL_Texture*>(resource, texture));
			SDL_FreeSurface(spriteSheet);
			return texture;
		}

		return NULL;
	}

	SDL_Texture* getTextureFromImage(/** The string pointing to the resource */const char* resource,
		/** The SDL_Renderer to render the Texture with */ SDL_Renderer* ren) {
		if (textures_.count(resource) > 0) {
			return textures_[resource];
		}

		SDL_Surface* spriteSheet = IMG_Load(resource);

		if (spriteSheet == NULL) {
			SDL_Log("Failed to allocate surface");
		}
		else {
			SDL_Log("Allocated a bunch of memory to create identical game character");
			// Create a texture from our surface
			// Textures run faster and take advantage of hardware acceleration
			SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 4, 255, 17));
			SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
			textures_.insert(std::pair<const char*, SDL_Texture*>(resource, texture));
			SDL_FreeSurface(spriteSheet);
			return texture;
		}

		return NULL;
	}

	static void reset() {
		delete inst_;
		inst_ = NULL;
	}

private:
	/** Private constructor */
	ResourceManager() {}

	/** Private destructor */
	~ResourceManager() {
		for (auto it = textures_.begin(); it != textures_.end(); ++it) {
			SDL_DestroyTexture(it->second);
			SDL_Log("Freed Texture: %s", it->first);
		}
	}

	/** The singleton instance */
	static ResourceManager* inst_;

	/** Mapping of cached SDL_Textures */
	std::map<const char*, SDL_Texture*> textures_;
};

#endif

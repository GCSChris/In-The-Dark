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

	/** Get the dimensions (width, height) of a given resource's Surface. */
	SDL_Point getIMGDimensions(/** The string pointing to the surface */ std::string resource) {
		SDL_Surface* surface = IMG_Load(resource.c_str());

		/* // Shouldnt show user.
		if (surface == NULL) {
			SDL_Log("Failed to allocate surface");
		}
		*/

		SDL_Point dimensions = { surface->w, surface->h };
		return dimensions;
	}

	/** Get a texture loaded from an image. */
	SDL_Texture* getTextureFromImage(/** The string pointing to the resource */std::string resource,
		/** The SDL_Renderer to render the Texture with */ SDL_Renderer* ren) {
		if (textures_.count(resource) > 0) {
			return textures_[resource];
		}

		SDL_Surface* spriteSheet = IMG_Load(resource.c_str());

		if (spriteSheet == NULL) {
			SDL_Log("Failed to allocate surface - image not found!");
			return NULL;
		}
		else {
			//SDL_Log("Allocating memory for texture.");
			SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
			textures_.insert(std::pair<std::string, SDL_Texture*>(resource, texture));
			SDL_FreeSurface(spriteSheet);
			return texture;
		}
	}

	/** Destroy all textures in this ResourceManager's map of allocated SDL_Textures. */
	void cleanUp() {
		for (auto it = textures_.begin(); it != textures_.end(); ++it) {
			SDL_DestroyTexture(it->second);
		}
	}

private:
	/** Private constructor */
	ResourceManager() {}

	/** Private destructor */
	~ResourceManager() {}

	/** The singleton instance */
	static ResourceManager* inst_;

	/** Mapping of cached SDL_Textures */
	std::map<std::string, SDL_Texture*> textures_;
};

#endif

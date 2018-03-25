#ifndef RESOURCEMANGER_H
#define RESOURCEMANGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

/** A ResourceManager singleton class */
class ResourceManager {
public:
	/**
	* Returns the instance of the ResourceManager.
	*/
    static ResourceManager& instance() {
        if (inst_ == NULL) {
			inst_ = new ResourceManager();
		} 
        return *inst_;
    }

	/** 
	* Returns a SDL_Texture. 
	*/
    SDL_Texture* getTexture(/** The string pointing to the resource */std::string resource,
		/** The SDL_Renderer to render the Texture with */ SDL_Renderer* ren) {
        if (textures_.count(resource) > 0) {
            return textures_[resource];
        }
        
        SDL_Surface* spriteSheet = IMG_Load(resource.c_str());
        
        if (spriteSheet == NULL){
            SDL_Log("Failed to allocate surface");
        } else {
            SDL_Log("Allocated a bunch of memory to create identical game character");
		    // Create a texture from our surface
            // Textures run faster and take advantage of hardware acceleration
			SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 4, 255, 17));
            SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
            textures_.insert(std::pair<std::string, SDL_Texture*>(resource, texture));
            SDL_FreeSurface(spriteSheet);
            return texture;
        }

        return NULL;
    }

	/**
	* Given a filepath to an image file, creates a SDL texture from the image.
	*/
	SDL_Texture* getTextureFromImage(/** The string pointing to the resource */std::string resource,
		/** The SDL_Renderer to render the Texture with */ SDL_Renderer* ren) {
		if (textures_.count(resource) > 0) {
			return textures_[resource];
		}

		SDL_Surface* spriteSheet = IMG_Load(resource.c_str());

		if (spriteSheet == NULL) {
			SDL_Log("Failed to allocate surface");
		}
		else {
			SDL_Log("Allocated a bunch of memory to create identical game character");
			// Create a texture from our surface
			// Textures run faster and take advantage of hardware acceleration
			//SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 4, 255, 17));
			
			SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
			textures_.insert(std::pair<std::string, SDL_Texture*>(resource, texture));
			SDL_FreeSurface(spriteSheet);
			return texture;
		}

		return NULL;
	}

	/** Get the dimensions (width, height) of a given resource's Surface. */
	SDL_Point getIMGDimensions(/** The string pointing to the surface */ std::string resource) {
		SDL_Surface* surface = IMG_Load(resource.c_str());

		if (surface == NULL) {
			SDL_Log("Failed to allocate surface");
		}

		SDL_Point dimensions = { surface->w, surface->h };
		return dimensions;
	}

	/** 
	* Returns the true-type font at the given path.
	*/
	TTF_Font* getFont(/** The resource path */ std::string resource,
		/** The size of the font */ int size) {
		if (fonts_.count(resource) > 0) {
			return fonts_[resource];
		}

		TTF_Font* font = TTF_OpenFont(resource.c_str(), size);

		if (font == NULL) {
			SDL_Log("Failed to allocate font");
		}
		else {
			SDL_Log("Allocating font");
			fonts_.insert(std::pair<std::string, TTF_Font*>(resource, font));
			return font;
		}

		return NULL;
	}
	
	/**
	* Resets the instance to completely clear the resource manager.
	*/
    static void reset() {
        delete inst_;
        inst_ = NULL;
    }

private:
	/** Private constructor */
    ResourceManager() {}
	
	/** Private destructor */
    ~ResourceManager() {
        for (auto it=textures_.begin(); it!=textures_.end(); ++it) {
            SDL_DestroyTexture(it->second);
            SDL_Log("Freed Texture: %s", it->first);
        } 

		for (auto it = fonts_.begin(); it != fonts_.end(); ++it) {
			TTF_CloseFont(it->second);
			SDL_Log("Freed Font: %s", it->first);
		}
    }
    
	/** The singleton instance */
	static ResourceManager* inst_;

	/** Mapping of cached SDL_Textures */
    std::map<std::string, SDL_Texture*> textures_;
	/** Mapping of cached TTF_Font */
	std::map<std::string, TTF_Font*> fonts_;
};

#endif

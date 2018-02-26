#ifndef RESOURCEMANGER_H
#define RESOURCEMANGER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
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
        
        if (spriteSheet==NULL){
            SDL_Log("Failed to allocate surface");
        } else {
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

	/** Returns the true-type font at the given path */
	TTF_Font* getFont(/** The resource path */ const char* resource,
		/** The size of the font */ int size) {
		if (fonts_.count(resource) > 0) {
			return fonts_[resource];
		}

		TTF_Font* font = TTF_OpenFont(resource, size);

		if (font == NULL) {
			SDL_Log("Failed to allocate font");
		}
		else {
			SDL_Log("Allocating font");
			fonts_.insert(std::pair<const char*, TTF_Font*>(resource, font));
			return font;
		}

		return NULL;
	}
	
	/** Returns a Mix_Music loaded using the given path */
	Mix_Music* getMusic(/** The path for the music */ const char* resource) {
		if (music_.count(resource) > 0) {
			return music_[resource];
		}

		Mix_Music* music = Mix_LoadMUS(resource);

		if (music == NULL) {
			SDL_Log("Failed to allocate music");
		}
		else {
			SDL_Log("Allocating music");
			music_.insert(std::pair<const char*, Mix_Music*>(resource, music));
			return music;
		}

		return NULL;
	}

	/** Returns a playable sound chunk from the given resource path */
	Mix_Chunk* getSFX(/** The resource path */const char* resource) {
		if (sounds_.count(resource) > 0) {
			return sounds_[resource];
		}

		Mix_Chunk* sfx = Mix_LoadWAV(resource);

		if (sfx == NULL) {
			SDL_Log("Failed to allocate sfx");
		}
		else {
			SDL_Log("Allocating sfx");
			sounds_.insert(std::pair<const char*, Mix_Chunk*>(resource, sfx));
			return sfx;
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
        for (auto it=textures_.begin(); it!=textures_.end(); ++it) {
            SDL_DestroyTexture(it->second);
            SDL_Log("Freed Texture: %s", it->first);
        } 
		
		for (auto it = music_.begin(); it != music_.end(); ++it) {
			Mix_FreeMusic(it->second);
			SDL_Log("Freed Music: %s", it->first);
		}

		for (auto it = sounds_.begin(); it != sounds_.end(); ++it) {
			Mix_FreeChunk(it->second);
			SDL_Log("Freed SFX: %s", it->first);
		}

		for (auto it = fonts_.begin(); it != fonts_.end(); ++it) {
			TTF_CloseFont(it->second);
			SDL_Log("Freed Font: %s", it->first);
		}
    }
    
	/** The singleton instance */
	static ResourceManager* inst_;

	/** Mapping of cached SDL_Textures */
    std::map<const char*, SDL_Texture*> textures_;
	/** Mapping of cached Mix_Music */
	std::map<const char*, Mix_Music*> music_;
	/** Mapping of cached Mix_Chunk */
	std::map<const char*, Mix_Chunk*> sounds_;
	/** Mapping of cached TTF_Font */
	std::map<const char*, TTF_Font*> fonts_;
};

#endif

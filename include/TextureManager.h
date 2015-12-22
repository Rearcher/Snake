#ifndef _TextureManager_
#define _TextureManager_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <map>

class TextureManager {
public:
	bool load(std::string fileName, std::string id, 
			SDL_Renderer *p_Renderer);

	void draw(std::string id, int x, int y, int width, int height, 
			SDL_Renderer *p_Renderer, SDL_RendererFlip filp = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int height,
			int currentRow, int currentFrame, SDL_Renderer *p_Renderer,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

	void clearFromTextureMap(std::string id);

	static TextureManager *Instance();

private:
	std::map<std::string, SDL_Texture*> m_textureMap;
	
	TextureManager() {}

	static TextureManager *s_pInstance;
};

typedef TextureManager TheTextureManager;
#endif  /* texture manager */

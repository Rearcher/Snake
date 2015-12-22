#include "TextureManager.h"

bool TextureManager::load(std::string fileName, std::string id, 
		SDL_Renderer *pRenderer) {
	SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == nullptr)
		return false;

	SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != nullptr) {
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width,
		int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
			&destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width,
		int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer,
		SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
			&destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id) {
	if (m_textureMap.find(id) != m_textureMap.end())
		m_textureMap.erase(id);
}

TextureManager* TextureManager::Instance() {
	if (s_pInstance == nullptr) {
		s_pInstance = new TextureManager();
		return s_pInstance;
	}
	return s_pInstance;
}

TextureManager* TextureManager::s_pInstance = nullptr;

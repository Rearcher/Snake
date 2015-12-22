#ifndef _Game_
#define _Game_

#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "GameObject.h"

#include <iostream>
#include <vector>

class Game {
public:

	bool init(const char*, int, int, int, int, int);

	void render();
	void update();
	void clean();
	void quit() {
		clean();
	}

	void handleEvents();

	bool running();

	static Game *Instance() {
		if (s_pInstance == nullptr) {
			s_pInstance = new Game();
		}
		return s_pInstance;
	}

	SDL_Renderer *getRenderer() const {
		return m_pRenderer;
	}

	void exitGame() {
		m_bRunning = false;
	}

	GameStateMachine *getStateMachine() {
		return m_pGameStateMachine;
	}
private:
	Game() {}
	~Game() {}

	SDL_Window *m_pWindow;
	SDL_Renderer *m_pRenderer;

	SDL_Texture *m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	bool m_bRunning;
	int m_currentFrame;

	static Game *s_pInstance;

	std::vector<GameObject*> m_gameObjects;
	GameStateMachine *m_pGameStateMachine;
};

typedef Game TheGame;

#endif

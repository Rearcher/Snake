#include "Game.h"

Game* Game::s_pInstance = nullptr;

bool Game::init(const char *title, int xpos, int ypos, int width,
		int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success\n";
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != nullptr) {
			std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0); 
            
			if (m_pRenderer != nullptr) {
                std::cout << "renderer creation success\n";
			    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			} else {
				
				std::cout << "renderer init fail\n";
				return false;
			}
		} else {
			std::cout << "window init fail\n";
	 	    return false;
		}
	} else {
		std::cout << "SDL init fail\n";
		return false;
	}
	
	m_Width = width;
	m_Height = height;

	std::cout << "init success\n";
	m_bRunning = true;

	// InputHandler init
	// GameStateMachine init
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());
	// TextureManager init
	return true;
}

void Game::render() {
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::update() {
	m_pGameStateMachine->update();
}

void Game::handleEvents() {
	TheInputHandler::Instance()->update();
}

void Game::clean() {
	std::cout << "clean game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

bool Game::running() {
	return m_bRunning;
}

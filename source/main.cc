#include "Game.h"
#include <cstdlib>

const int FPS = 150;
const int DELAY_TIME = 1000.0f / FPS;

int main() {
	srand((int)time(0));
	
	Uint32 frameStart, frameTime;
	
	if (TheGame::Instance()->init("Snake", 100, 100, 640, 480, 0)) {
		std::cout << "game init success\n";
		
		while (TheGame::Instance()->running()) {
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	} else {
		std::cout << "game init failed\n";
	}

	TheGame::Instance()->clean();
	return 0;
}

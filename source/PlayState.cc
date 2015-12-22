#include "PlayState.h"
#include "Snake.h"
#include "Game.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (auto gameObject : m_gameObjects)
		gameObject->update();

	if (m_gameObjects.size() > 0 && checkBorderCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]))) {
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
	}
}

void PlayState::render() {
	for (auto gameObject : m_gameObjects)
		gameObject->draw();
}

bool PlayState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/body.png",
				"snake", TheGame::Instance()->getRenderer())) {
		std::cerr << "open assets/body.png failed\n";
		return false;
	}

	GameObject *snake = new Snake();
	snake->load(new LoaderParams(100, 100, 33, 33, "snake", 1));
	m_gameObjects.push_back(snake);

	m_textureIDList.push_back("snake");
	
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit() {
	for (auto gameObject : m_gameObjects)
		gameObject->clean();
	m_gameObjects.clear();

	for (auto id : m_textureIDList)
		TheTextureManager::Instance()->clearFromTextureMap(id);
	m_textureIDList.clear();

	std::cout << "exiting PlayState\n";
	return true;
}

void PlayState::resume() {

}

bool PlayState::checkBorderCollision(SDLGameObject *p1) {
	int left, right, top, bottom;
	int left_margin, right_margin, top_margin, bottom_margin;

	left = p1->getPosition().getX();
	right = p1->getPosition().getX() + p1->getWidth();
	top = p1->getPosition().getY();
	bottom = p1->getPosition().getY() + p1->getHeight();

	left_margin = 0;
	right_margin = TheGame::Instance()->getWidth();
	top_margin = 0;
	bottom_margin = TheGame::Instance()->getHeight();


	if (left <= left_margin) return true;
	if (right >= right_margin) return true;
	if (top <= top_margin) return true;
	if (bottom >= bottom_margin) return true;

	return false;
}


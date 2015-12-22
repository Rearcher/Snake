#include "PlayState.h"
#include "Snake.h"
#include "Game.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
	// pause state
	for (auto gameObject : m_gameObjects)
		gameObject->update();

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


#include "NextLevelState.h"
#include "Game.h"
#include <iostream>

const std::string NextLevelState::m_nextLevelID = "NEXT";

void NextLevelState::update() {
	m_object->update();

	if (SDL_GetTicks() - m_enterTime > 1000)
		TheGame::Instance()->getStateMachine()->popState();
}

void NextLevelState::render() {
	m_object->draw();
}

bool NextLevelState::onEnter() {
	
	m_enterTime = SDL_GetTicks();

	if (!TheTextureManager::Instance()->load(m_filename, m_filename,
				TheGame::Instance()->getRenderer())) {
		std::cout << "next level texture open failed\n";
		return false;
	}
	
	m_object = new SDLGameObject();
	m_object->load(new LoaderParams(0, 0, TheGame::Instance()->getWidth(),
				TheGame::Instance()->getHeight(), m_filename, 1));
	m_object->setCurrentFrame(0);

	m_textureIDList.push_back(m_filename);
	std::cout << "entering NextLevelState\n";
}

bool NextLevelState::onExit() {
	m_object->clean();

	for (auto id : m_textureIDList)
		TheTextureManager::Instance()->clearFromTextureMap(id);
	m_textureIDList.clear();

	std::cout << "exiting NextLevelState\n";
}

void NextLevelState::resume() {

}

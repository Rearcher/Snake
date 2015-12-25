#include "ClearState.h"
#include "Game.h"

const std::string ClearState::m_clearID = "CLEAR";

void ClearState::s_clearToMain() {
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void ClearState::update() {
	m_background->update();
	m_button->update();
}

void ClearState::render() {
	m_background->draw();
	m_button->draw();
}

void ClearState::resume() {
	
}

bool ClearState::onEnter() {

	if(!TheTextureManager::Instance()->load("assets/end.png",
				"end", TheGame::Instance()->getRenderer())) {
		std::cout << "ClearState file load failed\n";	
		return false;
	}

	if(!TheTextureManager::Instance()->load("assets/main.png",
				"mainbutton", TheGame::Instance()->getRenderer())) {
		std::cout << "ClearState file load failed\n";	
		return false;
	}
	
	m_background = new SDLGameObject();
	m_button = new MenuButton(s_clearToMain);
	
	m_background->load(new LoaderParams(0, 0, TheGame::Instance()->getWidth(),
				TheGame::Instance()->getHeight(), "end", 1));
	m_background->setCurrentFrame(0);

	m_button->load(new LoaderParams(200, 200, 200, 80, "mainbutton", 3));

	m_textureIDList.push_back("end");
	m_textureIDList.push_back("mainbutton");

	std::cout << "entering ClearState\n";
	return true;
}

bool ClearState::onExit() {
	m_background->clean();
	m_button->clean();
	
	std::cout << "exiting ClearState\n";
	return true;
}

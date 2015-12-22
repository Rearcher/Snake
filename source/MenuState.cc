#include "MenuState.h"
#include "Game.h"
#include "MenuButton.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
	for (auto gameObject : m_gameObjects)
		gameObject->update();
}

void MenuState::render() {
	for (auto gameObject : m_gameObjects)
		gameObject->draw();
}

bool MenuState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/button.png", 
				"playbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/exit.png",
				"exitbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	
	GameObject *button1 = new MenuButton(s_menuToPlay);
	button1->load(new LoaderParams(100, 100, 400, 100, "playbutton", 3));
	
	GameObject *button2 = new MenuButton(s_exitFromMenu);
	button2->load(new LoaderParams(100, 300, 400, 100, "exitbutton", 3));

	m_textureIDList.push_back("playbutton");
	m_textureIDList.push_back("exitbutton");

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit() {
	for (auto gameObject : m_gameObjects)
				gameObject->clean();
	m_gameObjects.clear();

	for (auto id : m_textureIDList)
		TheTextureManager::Instance()->clearFromTextureMap(id);
	m_textureIDList.clear();

	std::cout << "exiting MenuState\n";
	return true;
}

void MenuState::resume() {
	
}

void MenuState::s_menuToPlay() {
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	std::cout << "Play button clicked\n";
}

void MenuState::s_exitFromMenu() {
	std::cout << "Exit button clicked\n";
	TheGame::Instance()->exitGame();
}

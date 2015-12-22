#include "PauseState.h"
#include "Game.h"
#include "MenuButton.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain() {
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay() {
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update() {
	for (auto gameObject : m_gameObjects)
		gameObject->update();
}

void PauseState::render() {
	for (auto gameObject : m_gameObjects)
		gameObject->draw();
}

void PauseState::resume() {

}

bool PauseState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/resume.png", "resumebutton",
				TheGame::Instance()->getRenderer())) {
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton",
				TheGame::Instance()->getRenderer())) {
		return false;
	}
	
	GameObject *button1 = new MenuButton(s_pauseToMain);
	button1->load(new LoaderParams(200, 200, 200, 80, "mainbutton", 3));

	GameObject *button2 = new MenuButton(s_resumePlay);
	button2->load(new LoaderParams(200, 300, 200, 80, "resumebutton", 2));

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	m_textureIDList.push_back("mainbutton");
	m_textureIDList.push_back("resumebutton");

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit() {
	for (auto gameObject : m_gameObjects)
				gameObject->clean();
	m_gameObjects.clear();

	for (auto id : m_textureIDList)
		TheTextureManager::Instance()->clearFromTextureMap(id);
	m_textureIDList.clear();

	std::cout << "exiting PauseState\n";
	return true;
}


#include "GameOverState.h"
#include "Game.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain() {
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay() {
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::resume() {

}

bool GameOverState::onEnter() {
	if(!TheTextureManager::Instance()->load("assets/gameover.png",
				"gameovertext", TheGame::Instance()->getRenderer())) {
		return false;
	}
		
	if(!TheTextureManager::Instance()->load("assets/main.png",
				"mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
			
	if(!TheTextureManager::Instance()->load("assets/restart.png",
				"restartbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}

	GameObject *gameOverText = new AnimatedGraphic();
	gameOverText->load(new LoaderParams(200, 100, 190, 30, "gameovertext", 2, 0, 2));

	GameObject *button1 = new MenuButton(s_gameOverToMain);
	button1->load(new LoaderParams(200, 200, 200, 80, "mainbutton", 3));

	GameObject *button2 = new MenuButton(s_restartPlay);
	button2->load(new LoaderParams(200, 300, 200, 80, "restartbutton", 3));

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	m_textureIDList.push_back("gameovertext");
	m_textureIDList.push_back("mainbutton");
	m_textureIDList.push_back("restartbutton");

	std::cout << "entering GameOverState\n";
	return true;
}

bool GameOverState::onExit() {
	for (auto gameObject : m_gameObjects)
				gameObject->clean();
	m_gameObjects.clear();

	for (auto id : m_textureIDList)
		TheTextureManager::Instance()->clearFromTextureMap(id);
	m_textureIDList.clear();

	std::cout << "exiting GameOverState\n";
	return true;
}

void GameOverState::render() {
	for (auto gameObject : m_gameObjects)
		gameObject->draw();
}

void GameOverState::update() {
	for (auto gameObject : m_gameObjects)
		gameObject->update();
}

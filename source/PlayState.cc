#include "PlayState.h"
#include "Snake.h"
#include "Game.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}
	
	// m_body update
	m_head->update();
	
	// m_body update
	for (auto body : m_body)
		body->bodyUpdate();

	for (auto body : m_body)
		body->updatePosition();

	if (checkBorderCollision(dynamic_cast<SDLGameObject*>(m_head))) {
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
	}
}

void PlayState::render() {
//	for (auto gameObject : m_gameObjects)
//		gameObject->draw();
	m_head->draw();
	for (auto body : m_body)
		body->draw();
}

bool PlayState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/body.png",
				"snake", TheGame::Instance()->getRenderer())) {
		std::cerr << "open assets/body.png failed\n";
		return false;
	}

	Snake::cleanTurnPoints();
	
	Snake *snake = new Snake();
	snake->load(new LoaderParams(100, 100, 33, 33, "snake", 1));
	m_head = snake;
	
	// add body
	Snake *body1 = new Snake(), *body2 = new Snake, *body3 = new Snake;
	body1->load(new LoaderParams(67, 100, 33, 33, "snake", 1));
	body2->load(new LoaderParams(34, 100, 33, 33, "snake", 1));
	body3->load(new LoaderParams(1, 100, 33, 33, "snake", 1));
	m_body.push_back(body1);
	m_body.push_back(body2);
	m_body.push_back(body3);

	m_textureIDList.push_back("snake");
	
	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit() {
//	for (auto gameObject : m_gameObjects)
//		gameObject->clean();
//	m_gameObjects.clear();
	
	m_head->clean();
	
	for (auto body : m_body)
		body->clean();
	m_body.clear();

	for (auto id : m_textureIDList)
		TheTextureManager::Instance()->clearFromTextureMap(id);
	m_textureIDList.clear();
	
	Snake::cleanTurnPoints();

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


	if (left < left_margin) return true;
	if (right > right_margin) return true;
	if (top < top_margin) return true;
	if (bottom > bottom_margin) return true;

	return false;
}


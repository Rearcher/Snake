#include "PlayState.h"
#include "Snake.h"
#include "Game.h"
#include <iostream>
#include <cstdlib>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}
	
	bodyIncrease();
	// m_body update
	m_head->update();
	
	// m_body update
	for (auto body : m_body)
		body->bodyUpdate();

	for (auto body : m_body)
		body->updatePosition();

	if (checkBorderCollision(dynamic_cast<SDLGameObject*>(m_head))) {
//			checkBodyCollision()) {
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
	}
	
	// m_food update
	if (SDL_GetTicks() - foodTime > 15000) {
		produceFood();
		foodTime = SDL_GetTicks();
	}
	m_food->update();
}

void PlayState::render() {
//	for (auto gameObject : m_gameObjects)
//		gameObject->draw();
	m_head->draw();
	for (auto body : m_body)
		body->draw();

	m_food->draw();
}

bool PlayState::onEnter() {
	if (!TheTextureManager::Instance()->load("assets/body.png",
				"snake", TheGame::Instance()->getRenderer())) {
		std::cerr << "open assets/body.png failed\n";
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/food.png",
				"food", TheGame::Instance()->getRenderer())) {
		std::cerr << "open assets/food.png failed\n";
		return false;
	}
	
	Snake::cleanTurnPoints();
	
	Snake *snake = new Snake();
	snake->load(new LoaderParams(100, 100, body_size, body_size, "snake", 1));
	m_head = snake;
	
	// add body
	Snake *body1 = new Snake(), *body2 = new Snake, *body3 = new Snake;
	body1->load(new LoaderParams(67, 100, body_size, body_size, "snake", 1));
	body2->load(new LoaderParams(34, 100, body_size, body_size, "snake", 1));
	body3->load(new LoaderParams(1, 100, body_size, body_size, "snake", 1));
	m_body.push_back(body1);
	m_body.push_back(body2);
	m_body.push_back(body3);
	
	if (m_body.size() > 0)
		Snake::setBodyFlag(true);
	
	// add food
//	Food *food = new Food();
//	food->load(new LoaderParams(200, 200, food_size, food_size, "food", 1));
//	m_food = food;
	produceFood();
	foodTime = SDL_GetTicks();

	m_textureIDList.push_back("snake");
	m_textureIDList.push_back("food");

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

bool PlayState::bodyCollision(SDLGameObject *p1, SDLGameObject *p2) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();
	//If any of the sides from A
	if(bottomA <= topB) { return false; }
	if(topA >= bottomB) { return false; }
	if(rightA <= leftB) { return false; }
	if(leftA >= rightB) { return false; }

	return true;
}

bool PlayState::checkBodyCollision() {
	if (m_body.empty()) return false;

	for (auto body : m_body)
		if (bodyCollision(dynamic_cast<SDLGameObject*>(m_head), 
					dynamic_cast<SDLGameObject*>(body)))
			return true;

	return false;
}

void PlayState::produceFood() {
	int width = TheGame::Instance()->getWidth() - food_size;
	int height = TheGame::Instance()->getHeight() - food_size;

	int x = rand() % width;
	int y = rand() % height;

	Food *food = new Food();
	food->load(new LoaderParams(x, y, food_size, food_size, "food", 1));
	m_food = food;
}

void PlayState::bodyIncrease() {
	if (bodyCollision(dynamic_cast<SDLGameObject*>(m_head), 
				dynamic_cast<SDLGameObject*>(m_food))) {
		int x, y;
		Vector2D pos, vel;
		
		if (m_body.empty()) { // no body yet
			pos = m_head->getPosition();
			vel = m_head->getVelocity();

		} else {			  // already has some body
			pos = m_body.back()->getPosition();
			vel = m_body.back()->getPosition();
		}

		if (vel.getX() > 0 && vel.getY() == 0) {
			x = pos.getX() - body_size;
			y = pos.getY();
		} else if (vel.getX() < 0 && vel.getY() == 0) {
			x = pos.getX() + body_size;
			y = pos.getY();
		} else if (vel.getX() == 0 && vel.getY() < 0) {
			x = pos.getX();
			y = pos.getY() + body_size;
		} else if (vel.getX() == 0 && vel.getY() > 0) {
			x = pos.getX();
			y = pos.getY() - body_size;
		}

		Snake *body = new Snake();
		body->load(new LoaderParams(x, y, body_size, body_size, "snake", 1));
		m_body.push_back(body);
		body->draw();
		
		if (m_body.size() > 0)
			Snake::setBodyFlag(true);

		produceFood();
		foodTime = SDL_GetTicks();
	}
}

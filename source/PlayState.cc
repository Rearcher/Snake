#include "PlayState.h"
#include "Snake.h"
#include "Game.h"
#include <iostream>
#include <cstdlib>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
	if (m_initFlag) {
		TheGame::Instance()->getStateMachine()->pushState(
				new NextLevelState(m_levelFiles[m_currentLevel]));
		m_initFlag = false;
	}

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
/*
	if (checkBorderCollision(dynamic_cast<SDLGameObject*>(m_head))) {
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
	}
*/	
	if (checkBorderCollision(dynamic_cast<SDLGameObject*>(m_head)) ||
			checkBodyCollision()) {
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());

		delete m_head;
		m_head = new Snake();
		m_head->load(new LoaderParams(100, 100, body_size, body_size, "snake", 1));
		m_body.clear();
		
		Snake::cleanTurnPoints();

		produceFood();
		foodTime = SDL_GetTicks();
	}
	// m_food update
	if (SDL_GetTicks() - foodTime > 15000) {
		produceFood();
		foodTime = SDL_GetTicks();
	}
	m_food->update();
	
	m_map->update();

	// to new level
	if (m_body.size() >= m_nextThreshold[m_currentLevel]) {
		
		m_currentLevel++;
		if (m_currentLevel >= m_mapFiles.size()) {
			TheGame::Instance()->getStateMachine()->changeState(new ClearState());
			return;
		}
		
		TheGame::Instance()->getStateMachine()->pushState(
				new NextLevelState(m_levelFiles[m_currentLevel]));

		delete m_head;
		m_head = new Snake();
		m_head->load(new LoaderParams(100, 100, body_size, body_size, "snake", 1));
		m_body.clear();
	
		delete m_map;
		m_map = new Map(m_mapFiles[m_currentLevel]);
		if (!m_map->load("assets/blocks1.png", "block"))
			std::cout << "map load failed\n";

		Snake::cleanTurnPoints();
	}
}

void PlayState::render() {
//	for (auto gameObject : m_gameObjects)
//		gameObject->draw();
	m_head->draw();
	for (auto body : m_body)
		body->draw();

	m_food->draw();

	// draw map
	m_map->render();
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
	
	if (!TheTextureManager::Instance()->load("assets/level1.png",
				"level1", TheGame::Instance()->getRenderer())) {
		std::cerr << "open assets/level1.png failed\n";
		return false;
	}

	Snake::cleanTurnPoints();
	m_initFlag = true;

	m_head = new Snake();
	m_head->load(new LoaderParams(100, 100, body_size, body_size, "snake", 1));
	
	// add body
	Snake *body1 = new Snake(), *body2 = new Snake, *body3 = new Snake;
	body1->load(new LoaderParams(67, 100, body_size, body_size, "snake", 1));
	body2->load(new LoaderParams(34, 100, body_size, body_size, "snake", 1));
	body3->load(new LoaderParams(1, 100, body_size, body_size, "snake", 1));
//	m_body.push_back(body1);
//	m_body.push_back(body2);
//	m_body.push_back(body3);

	// add map
	m_mapFiles = {"assets/map0.txt", "assets/map1.txt"};
	m_levelFiles = {"assets/level1.png", "assets/level2.png"};
	m_currentLevel = 0;

	m_map = new Map(m_mapFiles[m_currentLevel]);
	if (!m_map->load("assets/blocks1.png", "block"))
		std::cout << "map load failed\n";

	if (m_body.size() > 0)
		Snake::setBodyFlag(true);
	
	// add level threshold
	m_nextThreshold = {5, 5};

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

	// check map collision
	Vector2D pos1, pos2;
	Vector2D head_v = m_head->getVelocity();
	Vector2D head_pos = m_head->getPosition();

	if (head_v.getX() > 0 && head_v.getY() == 0) {			// head is going right
		
		pos1.setPoint((float)(head_pos.getX()+body_size), (float)head_pos.getY());
		pos2.setPoint((float)(head_pos.getX()+body_size), (float)(head_pos.getY()+body_size));
	
	} else if (head_v.getX() < 0 && head_v.getY() == 0) { 	// head is going left
		
		pos1 = head_pos;
		pos2.setPoint((float)(head_pos.getX()), (float)(head_pos.getY()+body_size));

	} else if (head_v.getX() == 0 && head_v.getY() < 0) {  	// head is going up
		
		pos1 = head_pos;
		pos2.setPoint((float)(head_pos.getX()+body_size), (float)head_pos.getY());

	} else if (head_v.getX() == 0 && head_v.getY() > 0) {	// head is going down
		
		pos1.setPoint((float)(head_pos.getX()), (float)(head_pos.getY()+body_size));
		pos2.setPoint((float)(head_pos.getX()+body_size), (float)head_pos.getY()+body_size);

	}
	if (m_map->isInside(pos1) || m_map->isInside(pos2))
		return true;

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
	Vector2D pos1, pos2;
	Vector2D head_v = m_head->getVelocity();
	Vector2D head_pos = m_head->getPosition();

	if (head_v.getX() > 0 && head_v.getY() == 0) {			// head is going right
		
		pos1.setPoint((float)(head_pos.getX()+body_size), (float)head_pos.getY());
		pos2.setPoint((float)(head_pos.getX()+body_size), (float)(head_pos.getY()+body_size));
	
	} else if (head_v.getX() < 0 && head_v.getY() == 0) { 	// head is going left
		
		pos1 = head_pos;
		pos2.setPoint((float)(head_pos.getX()), (float)(head_pos.getY()+body_size));

	} else if (head_v.getX() == 0 && head_v.getY() < 0) {  	// head is going up
		
		pos1 = head_pos;
		pos2.setPoint((float)(head_pos.getX()+body_size), (float)head_pos.getY());

	} else if (head_v.getX() == 0 && head_v.getY() > 0) {	// head is going down
		
		pos1.setPoint((float)(head_pos.getX()), (float)(head_pos.getY()+body_size));
		pos2.setPoint((float)(head_pos.getX()+body_size), (float)head_pos.getY()+body_size);

	}

	for (unsigned int i = 1; i < m_body.size(); i++)
		if (m_body[i]->isInside(pos1) || m_body[i]->isInside(pos2))
			return true;
	return false;
}

void PlayState::produceFood() {
	int width = TheGame::Instance()->getWidth() - food_size;
	int height = TheGame::Instance()->getHeight() - food_size;

	int x = rand() % width;
	int y = rand() % height;
	
	Vector2D vec(x, y);
	Vector2D vec2(x + food_size, y + food_size);

	while (m_map->isInside(vec) || isInsideBody(vec) 
			|| m_map->isInside(vec2) || isInsideBody(vec2)) {
		x = rand() % width;
		y = rand() % height;
		vec = Vector2D(x, y);
	}

	Food *food = new Food();
	food->load(new LoaderParams(x, y, food_size, food_size, "food", 1));
	m_food = food;
}

void PlayState::bodyIncrease() {
	if (bodyCollision(dynamic_cast<SDLGameObject*>(m_head), 
				dynamic_cast<SDLGameObject*>(m_food))) {
		int x, y, turnindex;
		Vector2D pos, vel;
		
		if (m_body.empty()) { // no body yet
			pos = m_head->getPosition();
			vel = m_head->getVelocity();
			turnindex = m_head->getNumTurnPoints();

			std::cout << "turn points: " << m_head->getNumTurnPoints() << "\n";

		} else {			  // already has some body
			pos = m_body.back()->getPosition();
			vel = m_body.back()->getVelocity();
			turnindex = m_body.back()->getTurnIndex();
		}
		
		std::cout << "pos: " << pos.getX() << ", " << pos.getY() << "\n";
		std::cout << "vel: " << vel.getX() << ", " << vel.getY() << "\n";

		if (vel.getX() > 0 && vel.getY() == 0) {
			std::cout << "it's going right\n";
			x = pos.getX() - body_size;
			y = pos.getY();
		} else if (vel.getX() < 0 && vel.getY() == 0) {
			std::cout << "it's going left\n";
			x = pos.getX() + body_size;
			y = pos.getY();
		} else if (vel.getX() == 0 && vel.getY() < 0) {
			std::cout << "it's going up\n";
			x = pos.getX();
			y = pos.getY() + body_size;
		} else if (vel.getX() == 0 && vel.getY() > 0) {
			std::cout << "it's going down\n";
			x = pos.getX();
			y = pos.getY() - body_size;
		}

		Snake *body = new Snake();
		body->load(new LoaderParams(x, y, body_size, body_size, "snake", 1));
		body->setTurnIndex(turnindex);
		body->setVelocity(vel);
		m_body.push_back(body);

		std::cout << "turn points: " << Snake::getNumTurnPoints() << "\n";
		std::cout << "turnindex: " << turnindex << "\n";
//		body->draw();
//		body->bodyUpdate();
//		body->updatePosition();
		
		std::cout << "position: " << x << ", " << y << "\n";
		std::cout << "body increased\n";


		if (m_body.size() > 0)
			Snake::setBodyFlag(true);

		produceFood();
		foodTime = SDL_GetTicks();
	}
}

bool PlayState::isInsideBody(Vector2D v) {
	float x = v.getX();
	float y = v.getY();

	for (auto body : m_body) {
		Vector2D pos = body->getPosition();

		if (x > pos.getX() && x < pos.getX()+body_size
				&& y > pos.getY() && y < pos.getY()+body_size)
			return true;
	}
	
	return false;
}

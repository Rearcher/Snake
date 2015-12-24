#include "Snake.h"
#include "InputHandler.h"
#include <iostream>

std::vector<TurnPoint> Snake::m_turnPoints = {};
bool Snake::m_hasBody = false;
float Snake::m_speed = 1.0;
int Snake::m_size = 33;

void Snake::load(const LoaderParams *pParams) {
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	m_velocity = Vector2D(m_speed, 0);
	m_lastVelocity = Vector2D(0, 0);

	turnIndex = 0;
}

void Snake::draw() {
	SDLGameObject::draw();
}

void Snake::update() {
	m_lastVelocity = m_velocity;
	
	handleInput();
	SDLGameObject::update();
}

void Snake::clean() {

}

void Snake::handleInput() {
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		if ((m_velocity.getX() > 0 && m_velocity.getY() == 0) || 
				(m_velocity.getX() < 0 && m_hasBody))
			return;
		m_velocity = Vector2D(m_speed, 0);
		m_turnPoints.push_back(TurnPoint(m_position, m_velocity));
		return;
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		if ((m_velocity.getX() < 0 && m_velocity.getY() == 0) ||
				(m_velocity.getX() > 0 && m_hasBody))
			return;
		m_velocity = Vector2D(-m_speed, 0);
		m_turnPoints.push_back(TurnPoint(m_position, m_velocity));
		return;
	}
	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		if ((m_velocity.getX() == 0 && m_velocity.getY() < 0) ||
				(m_velocity.getY() > 0 && m_hasBody))
			return;
		m_velocity = Vector2D(0, -m_speed);
		m_turnPoints.push_back(TurnPoint(m_position, m_velocity));
		return;
	}
	
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		if ((m_velocity.getX() == 0 && m_velocity.getY() > 0) ||
				(m_velocity.getY() < 0 && m_hasBody))
			return;
		m_velocity = Vector2D(0, m_speed);
		m_turnPoints.push_back(TurnPoint(m_position, m_velocity));
		return;
	}
	return;
}
